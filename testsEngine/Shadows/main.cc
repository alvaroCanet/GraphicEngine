#include <iostream>


#include "GL/glew.h"     // --> multiplatform OpenGL support
#include "GLFW/glfw3.h"  // --> multiplatform Window support
#include "AntTweakBar.h"

extern "C" {
#include "../../deps/lua-5.2.2/src/lua.h"
#include "../../deps/lua-5.2.2/src/lualib.h"
#include "../../deps/lua-5.2.2/src/lauxlib.h"
}


#include "ESAT/core/window.h"
#include "ESAT/core/script.h"

#include "ESAT/core/Ptr/Scoped_ptr.h"
#include "ESAT/core/Ptr/Scoped_array.h"

#include "ESAT/core/Buffer.h"
#include <ESAT/core/Drawable.h>
#include <ESAT\core\UniformBlock.h>
#include <ESAT/core/Texture.h>
#include <ESAT/core/Camera.h>
#include <ESAT/core/Tools/Input.h>
#include <ESAT/core/Materials/Material.h>
#include <ESAT\core\Materials\Material_01.h>
#include <ESAT/core/Materials/Material_Ambient.h>
#include <ESAT\core\Materials\Material_Diffuse.h>
#include <ESAT/core/Materials/Material_Specular.h>
#include <ESAT/core/SkyBox.h>

// Mathematical functions and definitions used ------------
#define GLM_FORCE_RADIANS // --> use radians
#include "glm/glm.hpp"   // --> Mathematical functions
#include "glm/gtc/constants.hpp" // values like pi
#include "glm/gtc/matrix_transform.hpp"   // --> matrix transforms
#include "glm/gtc/type_ptr.hpp" // --> allows conversion from glm to pointers

typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
using glm::lookAt;      // lookAt(eye, center, up)
using glm::perspective; // perspective/fovy, aspect, zNear, zFar)
using glm::value_ptr;   // value_ptr(glm_type) --> returns pointer to dat
static const float PI = glm::pi<float>();
// --------------------------------------------------------
using namespace ESAT::core;
using namespace std;
using namespace Materials;

// OpenGL Initialization/Termination ----------------------
Window  *window_ = NULL;
Script *script_ = NULL;
void Init();
void Terminate();
// --------------------------------------------------------
scoped_ptr<Input> inputManager;

//-- VARIABLES GLOBALES

   TwBar *myBar;
   float rotSpeed = 0;

//Geometrys

   ref_ptr<Geometry> geo_;
   ref_ptr<Geometry> geo_1;
   ref_ptr<Geometry> geo_2;
   ref_ptr<Geometry> geo_3;
   ref_ptr<Geometry> cube_light01;
   ref_ptr<Geometry> geo_Secondcamera;

//Materials
   ref_ptr<Materials::Material_01>  mat_;
   ref_ptr<Materials::Material_01>  mat_1;
   ref_ptr<Materials::Material_Ambient> mat_ambient;
   ref_ptr<Materials::Material_Diffuse> mat_diffuse;
   ref_ptr<Materials::Material> mat_simple;
   ref_ptr<Materials::Material_Specular> mat_specular;
//Drawable
   ref_ptr<Drawable> DRAWBaseCube;
   ref_ptr<Drawable> DRAWBasePlane;
   ref_ptr<Drawable> DRAWPlaneForRenderToTex;
   ref_ptr<Drawable> DRAWCubeLight;
//UniformBlock
   ref_ptr<UniformBlock> uniform_block1;
   ref_ptr<UniformBlock> uniform_block2;
   ref_ptr<UniformBlock> uniform_block3;
   ref_ptr<UniformBlock> uniform_block4;
//Camera
   scoped_ptr<Camera> cam;
   scoped_ptr<Camera> CAMLight;
   scoped_ptr<Camera> CAMShadows;
//Textura
   ref_ptr<Texture> tex;
   ref_ptr<Texture> tex1;
   ref_ptr<Texture> texture_rock;
  

struct Mesh {
  GLuint vertex_buffer;
  GLuint index_buffer;
  GLuint num_triangles;
};

struct {
  Mesh cube;
} scene;



void Setup() {
  glClearColor(0.2f,0.2f,0.4f,1.0);
  inputManager.alloc();
  inputManager->Init(window_->window_);
}



void Draw() {
  double time = glfwGetTime();
  int width, height;
  
  glfwGetFramebufferSize(window_->window_, &width, &height);
  glViewport(0,0, width, height);
  
  // ----------------------------------------------
  // Draw Here
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 
  float light_pos[3];
  light_pos[0]= 2.0 *cos(time);
  light_pos[1]= 3.0;
  light_pos[2]= 2.0 *sin(time);

  float eye_pos[3];
  eye_pos[0]= cam->GetPosition().x;
  eye_pos[1]= cam->GetPosition().y;
  eye_pos[2]= cam->GetPosition().z;

  float far = cam->GetFar();

  uniform_block3->Set("u_lightPosition",light_pos);
  uniform_block3->Set("u_eyePosition",eye_pos);
  uniform_block3->Set("u_far",&far);

  /****TRANSFORMATIONS****/
  CAMLight->type =TPC_SHADOW;
  CAMLight->DrawOnBuffer(tex1.get());
  CAMLight->SetPosition(vec3(6.0*cos(time),3.0,6.0*sin(time)));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  CAMLight->TraverseNode(DRAWBaseCube.get(),&mat4(1.0f));
  CAMLight->TraverseNode(DRAWCubeLight.get(),&mat4(1.0f));
  CAMLight->DrawOnScreen();
 
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  CAMShadows->type = TPC;//TPC;//;
  CAMShadows->my_tex = CAMLight->my_tex;
  CAMShadows->SetPosition((vec3(6.0,6.0,6.0)));
  CAMShadows->TraverseNode(DRAWBaseCube.get(),&mat4(1.0f));

  TwDraw();
  }


static void CheckKey(GLFWwindow * window,int key,int code, int action ,int mode)
{
	if (action == GLFW_PRESS)
	{
		//TwWindowSize(400,400);
	}
}



int main(int argc, char **argv) {
  
  Init();
  Setup();

  int width, height;

  glfwGetFramebufferSize(window_->window_, &width, &height);
  glfwSetKeyCallback(window_->window_,(GLFWkeyfun)TwEventKeyGLFW);
  glfwSetCharCallback(window_->window_,(GLFWcharfun)TwEventCharGLFW);
 
  // send window size events to AntTweakBar
  glfwSetKeyCallback(window_->window_,CheckKey); // and call TwWindowSize in the function MyResize
/************************************************/
/****************GEOMETRY************************/
	geo_.alloc();
	geo_1.alloc();
	geo_2.alloc();
	geo_3.alloc();
	geo_Secondcamera.alloc();
	cube_light01.alloc();

	geo_1->createPlane(-5.0f,-2.5f,-5.0f,10.0f,10.0f);
	geo_->createCube(-1.0f,0.0f,1.0f,2.0f);
	geo_2->createPlane(-7.5f,0.0f,-5.0f,15.0f,15.0f);
	cube_light01->createCube(-1.0f,0.0f,1.0f,2.0f);
   
/************************************************/
/****************MATERIALS***********************/
	mat_.alloc();
	mat_1.alloc();
	mat_ambient.alloc();
	mat_diffuse.alloc();
	mat_simple.alloc();
	mat_specular.alloc();
	mat_->setData();
	mat_1->setData();
	mat_simple->setInfoMaterial();
	mat_ambient->setData();
	mat_diffuse->setData();
	mat_specular->setData();

/***********************************************/
/****************TEXTURES***********************/
	
	tex1.alloc();
	tex.alloc();

	tex1->CreateRenderToTexture();

/***********************************************/	
/****************UNIFORMS***********************/
	
	uniform_block1.alloc();
	uniform_block2.alloc();
	uniform_block3.alloc();
	uniform_block4.alloc();

	float color_[4] = {1.0f,0.0f,0.0f,1.0f};
	float intensity[1] ={ 0.0f};
	float intensity_diffuse[1] ={ 0.6f};
	float lightcolor_[4] = {1.0f,0.0f,0.0f,1.0f};
	float intensity_brightness[1] = {32.0f};
	float intensity_specular[1] = {0.8f};

	uniform_block1->InitUniform(mat_diffuse.get(),tex1.get());
	uniform_block1->Set("u_color",color_);
	uniform_block1->Set("u_ambientIntensity",intensity);
	uniform_block1->Set("u_lighColor",lightcolor_);
	uniform_block1->Set("u_IntensityDiffuse",intensity_diffuse);
	float color_2[4] = {0.0,1.0,0.0,1.0};
	uniform_block2->InitUniform(mat_1.get(),tex1.get());
	uniform_block3->InitUniform(mat_specular.get(),tex1.get());
	uniform_block3->Set("u_color",color_);
	uniform_block3->Set("u_ambientIntensity",intensity);
	uniform_block3->Set("u_lighColor",lightcolor_);
	uniform_block3->Set("u_IntensityDiffuse",intensity_diffuse);
	uniform_block3->Set("u_brightnessIntensity",intensity_brightness);
	uniform_block3->Set("u_specularIntensity",intensity_specular);
	float color_3[4] = {0.0,1.0,0.0,1.0};
	uniform_block4->InitUniform(mat_simple.get(),tex.get());
	uniform_block4->Set("u_color",color_3);

   

/************************************************/	
/****************DRAWABLES***********************/
	
	DRAWBaseCube.alloc();
	DRAWBasePlane.alloc();
	DRAWPlaneForRenderToTex.alloc();
	DRAWCubeLight.alloc();

	DRAWBaseCube->CreateDrawable(geo_.get(),uniform_block3.get());
    DRAWBasePlane->CreateDrawable(geo_1.get(),uniform_block3.get());
	DRAWPlaneForRenderToTex->CreateDrawable(geo_2.get(),uniform_block2.get());
	DRAWCubeLight->CreateDrawable(cube_light01.get(),uniform_block4.get());
	
	DRAWBaseCube->addChild(DRAWBasePlane.get());

	/*********TARNSFORMATIONS*******************/
	DRAWBaseCube->Scale(vec3(0.5f,0.5f,0.5f));
	DRAWPlaneForRenderToTex->Scale(vec3(0.5f,0.5f,0.5f));
	DRAWCubeLight->Scale(vec3(0.5f,0.5f,0.5f));
   
/*********************************************/		
/****************CAMERA***********************/
	cam.alloc();
	CAMLight.alloc();
	CAMShadows.alloc();
	cam->Init( &cam->ChangePerspective(60.0f,1.0f,14.0f,0.01f),&cam->ChangeLookAt(vec3(20,20,20), vec3(0,0,0), vec3(0,1,0)),TPC_NORMAL);
	CAMLight->Init(&CAMLight->ChangePerspective(60.0f,1.0f ,25.0f, 0.01f),&CAMLight->ChangeLookAt(vec3(6 ,6, 6), vec3(0,0,0), vec3(0,1,0)),TPC_NORMAL);
	CAMShadows->Init(&CAMShadows->ChangePerspective(60.0f,1.0f, 25.0f, 0.01f),&CAMShadows->ChangeLookAt(vec3(0 , 0, 6), vec3(0,0,0), vec3(0,1,0)),TPC);
 
/*********************************************/	

    //On Enter Frame
    while(window_->WindowsExist())
	{
		Draw();
		window_->SwapBuffers();
		window_->ProcessEvents();
	}
  
  Terminate();
  return 0;
}



extern "C" {
  static int l_cppfunction(lua_State *L) {
    
	window_ = new Window();
	if(window_->Init(800,600)==0)
	{
		cout <<"**Open Window OK" << endl;
	}
	
	// Send the new window size to AntTweakBar
    TwWindowSize(800, 600);

	if(window_->WindowsExist())
	{
		window_->MakeContext();
		glewInit();
	}
	else 
	{
		Terminate();
		exit(-2);
	}
    
	return 1;
  }
}

void Init() {

	script_= new Script();
	script_->Init_("../lua_files/example_printflua.lua",l_cppfunction,"cppfunction");
	TwInit(TW_OPENGL, NULL);
	// or
	//TwInit(TW_OPENGL_CORE, NULL); // for core profile
	myBar = TwNewBar("NameOfMyTweakBar");
	TwAddVarRW(myBar, "NameOfMyVariable",TW_TYPE_INT8, &rotSpeed, "adsfdsfsd");
}

void Terminate() {
 
	if(window_)
	{
		window_->FinishWindow();
	}
}

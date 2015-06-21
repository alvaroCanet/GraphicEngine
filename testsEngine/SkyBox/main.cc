#include <iostream>
#include "GL/glew.h"     // --> multiplatform OpenGL support
#include "GLFW/glfw3.h"  // --> multiplatform Window support
#include "AntTweakBar.h"
//Mine
#include "ESAT/core/window.h"
#include "ESAT/core/script.h"
#include "ESAT/core/Ptr/Scoped_ptr.h"
#include "ESAT/core/Ptr/Scoped_array.h"
#include <ESAT/core/Camera.h>
#include <ESAT/core/Tools/Input.h>
#include <ESAT/core/SkyBox.h>
// --------------------------------------------------------

using namespace ESAT::core;
using namespace std;
using namespace Materials;

//-- VARIABLES GLOBALES , CABECERAS
Window  *window_ = NULL;
Script *script_ = NULL;
TwBar *myBar;

scoped_ptr<Input> inputManager;
//Camera
scoped_ptr<Camera> CAMShadows;
//Sky
ref_ptr<CSkybox> skybox;

float TW_LookAt[] = {0.0f,0.0f,1.0f};
int   TW_Autorotate = 0;
int TW_RotateAxis = 0;
bool TW_ChangeSky = false;
int selectedSky = 0;
float speed = 0.0f;

void Init();
void Terminate();
// --------------------------------------------------------



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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(TW_ChangeSky == true)
  {
	  if(selectedSky == 0)
	  {
		  selectedSky =1;
		  skybox->loadSkybox("../assets/","sp3front.jpg","sp3back.jpg","sp3left.jpg","sp3right.jpg","sp3top_.jpg","sp3bot.jpg");
	  }
	  else
	  {
		  skybox->loadSkybox("../assets/","jajlands1_ft.jpg", "jajlands1_bk.jpg", "jajlands1_rt.jpg", "jajlands1_lf.jpg", "jajlands1_up.jpg", "jajlands1_dn.jpg");
		  selectedSky = 0;
	  }
	  TW_ChangeSky = false;
  }
  if(TW_Autorotate == true)
  {
	  switch(TW_RotateAxis)
	  {
		 case 0: CAMShadows->ChangeLookAt(vec3(0,0,0),vec3(1*cos(time*0.5),0*cos(time*0.5), 1*sin(time*0.5)), vec3(0,1,0));break;
		 case 1: CAMShadows->ChangeLookAt(vec3(0,0,0),vec3(0,1*cos(time*0.5),1*sin(time*0.5)), vec3(0,1,0));break;
		 case 2: CAMShadows->ChangeLookAt(vec3(0,0,0),vec3(1*cos(time*0.5),1*cos(time*0.5), 1*sin(time*0.5)), vec3(0,1,0));break;
		 default :CAMShadows->ChangeLookAt(vec3(0,0,0),vec3(1*cos(time*0.5),0*cos(time*0.5), 1*sin(time*0.5)), vec3(0,1,0));break; 

	  };
  }
  else
  {
	   CAMShadows->ChangeLookAt(vec3(0,0,0),vec3(TW_LookAt[0],TW_LookAt[1],TW_LookAt[2]), vec3(0,1,0));
  }
 
  skybox->renderSkybox(&CAMShadows->view_,&CAMShadows->projection_);

  // ----------------------------------------------
  TwDraw();
  }


int main(int argc, char **argv) {
  
  Init();
  Setup();

  int width, height;

  glfwGetFramebufferSize(window_->window_, &width, &height);

/************************************************/
/****************GEOMETRY************************/

/************************************************/
/****************MATERIALS***********************/

/************************************************/
/****************TEXTURES************************/

/************************************************/	
/****************UNIFORMS************************/

/************************************************/	
/****************DRAWABLES***********************/
	
/************************************************/		
/****************CAMERA**************************/
	
	CAMShadows.alloc();
	CAMShadows->Init(&CAMShadows->ChangePerspective(60.0f,1.0f, 25.0f, 0.01f)
					,&CAMShadows->ChangeLookAt(vec3(0, 0, 0), vec3(0,0,3)
					,vec3(0,1,0)),TPC_NORMAL);
 
/************************************************/	

/************************************************/	
/****************SKY*****************************/
	
	skybox.alloc();
	skybox->Init();
	skybox->loadSkybox("../assets/","jajlands1_ft.jpg", "jajlands1_bk.jpg", "jajlands1_rt.jpg", "jajlands1_lf.jpg", "jajlands1_up.jpg", "jajlands1_dn.jpg");

/************************************************/

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
	myBar = TwNewBar("SkyBox");
	TwAddVarRW(myBar, "ObjRotation", TW_TYPE_QUAT4F, &TW_LookAt," label='Object rotation' opened=true help='Change the object orientation.' ");
	TwAddVarRW(myBar, "AutoRotate", TW_TYPE_BOOL32, &TW_Autorotate," label='Auto-rotate' key=space help='Toggle auto-rotate mode.' ");
	TwAddVarRW(myBar, "Axis", TW_TYPE_INT8, &TW_RotateAxis," label='Axis' key=space help='Toggle auto-rotate mode.' ");
	TwAddVarRW(myBar, "Speed", TW_TYPE_DOUBLE, &speed," label='Speed speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");
	TwAddVarRW(myBar, "Change Sky", TW_TYPE_BOOL32, &TW_ChangeSky," label='Change Sky' key=space help='Toggle auto-rotate mode.' ");
}

void Terminate() {
 
	if(window_)
	{
		window_->FinishWindow();
	}
}

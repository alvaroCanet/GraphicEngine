#include <ESAT\core\Camera.h>

#include "glm/glm.hpp"   // --> Mathematical functions
#include "glm/gtc/constants.hpp" // values like pi
#include "glm/gtc/matrix_transform.hpp"   // --> matrix transforms
#include "glm/gtc/type_ptr.hpp" // --> allows conversion from glm to pointers

typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
using glm::lookAt;      // lookAt(eye, center, up)
using glm::perspective; // perspective/fovy, aspect, zNear, zFar)

namespace ESAT {
namespace core {
	
	Camera::Camera()
	{
		visitor.alloc();
	}

	Camera::~Camera(){}

	void Camera::Init(mat4 *proj,mat4 *view,TYPE_CAMERA type_)
	{
		view_ = (*view);
		projection_  = (*proj);
		type = type_;
	}

	mat4 Camera::ChangePerspective(float fovy_,float aspect_,float far_,float near_)
	{
		fovy = fovy_;
		aspect = aspect_;
		far = far_;
		near = near_;
		
		projection_ = perspective(fovy,aspect,near,far);
		
		return projection_;
	}

	mat4 Camera::ChangeLookAt(vec3 cameraPosition_,vec3 cameraTarget_, vec3 upVector_)
	{
		cameraPos = cameraPosition_;
		cameraTar = cameraTarget_;
		upVec = upVector_;
		view_ = lookAt(cameraPosition_, // the position of your camera, in world space
			           cameraTarget_,   // where you want to look at, in world space
			           upVector_ );     // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
		return view_;		
	}



	void Camera::SetPosition(vec3 cameraPos_)
	{
		cameraPos = cameraPos_;
		view_ = lookAt(cameraPos,cameraTar,upVec);
	}


	vec3 Camera::GetPosition()
	{
		return cameraPos;
	}

	float Camera::GetFar()
	{
		return far;
	}
	
	void Camera::TraverseNode(Node * node,mat4 *actual_matrix)
	{
		mat4 new_world_matrix = (*actual_matrix) * (*node->getLocalMatrix()) ;
		node->ModelMatrix = new_world_matrix;
		visitor->Process(node,&view_,&projection_,type,cameraPos,my_tex.get());
		for(size_t i = 0; i<node->numChilds();++i)
		{
			TraverseNode(node->getChild(i),&new_world_matrix);
		}
	}

	void Camera::DrawOnBuffer(Texture * tex,bool depth_)
	{
		my_tex = tex;
		GPU::Instance()->BindOnBuffer(&tex->texture_data.FramebufferId,depth_);
	}


	void Camera::DrawOnScreen(bool depth_)
	{
		GPU::Instance()->BindOnScreen(depth_);
	}
	

}
}
#ifndef _CAMERA_H__
#define _CAMERA_H__

#include <ESAT/core/Node.h>
#include <ESAT/core/Visitor.h>
#include <ESAT/core/ptr/scoped_ptr.h>
#include <ESAT/core/GPU.h>
#include <ESAT/core/Texture.h>

namespace ESAT {
namespace core {

	enum TYPE_CAMERA
	{
		TPC_NORMAL,
		TPC_SHADOW,
		TPC
	};

	class Camera 
	{
	
	public:
		Camera();
		~Camera();
		void Init(mat4 *proj,mat4 *view,TYPE_CAMERA type_);
		mat4 ChangeLookAt(vec3 cameraPos_,vec3 cameraTarg_,vec3 upVec);
		mat4 ChangePerspective(float fovy_,float aspect_,float far_,float near_);
		void SetPosition(vec3 cameraPos_);
		vec3 GetPosition();
		float GetFar();
		void TraverseNode(Node * node,mat4 *actual_matrix);
		void DrawOnBuffer(Texture * tex,bool depth_ = false);
		void DrawOnScreen(bool depth_ = false);
		
		TYPE_CAMERA type;
		ref_ptr<Texture>  my_tex;


		mat4 view_;
		mat4 projection_;
		scoped_ptr<Visitor>  visitor;
	private:
		
		
		
		vec3 cameraPos,cameraTar,upVec;

		float fovy,aspect,far,near;

		

		
	};
}
}
#endif
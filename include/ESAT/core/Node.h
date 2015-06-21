#ifndef _NODE_H__
#define _NODE_H__

#include "glm/glm.hpp"   // --> Mathematical functions
#include "glm/gtc/constants.hpp" // values like pi
#include "glm/gtc/matrix_transform.hpp"   // --> matrix transforms
#include "glm/gtx/transform.hpp"   // --> matrix transforms
#include <glm/gtc/type_ptr.hpp>
#include <ESAT/core/Ptr/Ref_ptr.h>
#include <vector>

#include <ESAT/core/type_defines.h>
#include <ESAT/core/Visitor.h>

typedef glm::mat4 mat4;
typedef glm::vec3 vec3;

enum TypeNode
{
	TP_Drawable,
	TP_Camera,
};

namespace ESAT {
namespace core {

	class Node : public Referenced 
	{
	private:
		//Node
		TypeNode type;
		Node * parent;
		std::vector<ref_ptr<Node>> children;
		
		//Transformations
		mat4 translation;
		mat4 scale;
		mat4 rotation;
		mat4 localMatrix;
		
		
		
	
	public:
		mat4 ModelMatrix;
		mat4 View;
		mat4 Projection;
		mat4 oldModelMatrix;

		//Node Functions
		void addChild(Node* node_);
		void removeChild(Node* node_);
		void changeParent(Node* node_);
		Node * getChild(int32 num_of_child);
		int32 numChilds();
		Node* rootNode();
		TypeNode getType();

		//Transformations Functions
		void Translate(vec3 value);
		void Scale(vec3 value);
		void Rotate(float value,vec3 orientation);
		void CalculateLocalMatrix();
		mat4* getLocalMatrix();

	protected:
		explicit Node(TypeNode type_);
		virtual ~Node();

	};
}
}
#endif
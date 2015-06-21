#ifndef _VISITOR_H__
#define _VISITOR_H__

#include "glm/glm.hpp"   // --> Mathematical functions
#include "ESAT/core/Materials/Material_Shadow.h"
#include <ESAT\core\Ptr\ref_ptr.h>
#include <ESAT\core\UniformBlock.h>

typedef glm::vec3 vec3;

namespace ESAT {
namespace core {

	class Node;

	class Visitor
	{
	public:
		Visitor();
		~Visitor();

		void Process(Node *node_,glm::mat4* view,glm::mat4 *proj,int type,vec3 eyePos,Texture* tex);

	private:

		ref_ptr<UniformBlock> shadowUniform; 
		ref_ptr<UniformBlock> shadowUniform2;

	};

}
}
#endif
#ifndef _DRAWABLE_H__
#define _DRAWABLE_H__

#include <ESAT\core\Ptr\ref_ptr.h>
#include <ESAT\core\UniformBlock.h>
#include <ESAT\core\Node.h>

namespace ESAT {
namespace core {
	
	namespace Materials
	{
		class Material;
	}

	class Geometry;
	

	class Drawable : public Node
	{ 

	private:

	ref_ptr<Geometry> geo_;
	ref_ptr<UniformBlock> uniform_block;
	bool compatible;

	public:                     
	
	Drawable();
	~Drawable();
	void CreateDrawable(Geometry *geo,UniformBlock *uniform);
	void Draw(mat4 *view,mat4 *proj);
	void DrawWithShadow(mat4 *view,mat4 *proj,vec3 eyePos,UniformBlock *uniformShad);
	void DrawShadowFinal(mat4 *view,mat4 *proj,UniformBlock *uniformShad,Texture * tex_);
	};



}
}

#endif
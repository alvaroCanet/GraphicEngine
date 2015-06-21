#ifndef _UNIFORMBLOCK_H__
#define _UNIFORMBLOCK_H__

#include <ESAT\core\type_defines.h>
#include <ESAT\core\Ptr\Ref_ptr.h>
#include <ESAT\core\type_defines.h>
#include <ESAT\core\Ptr\scoped_ptr.h>
#include <ESAT\core\UniformBlockIndex.h>
#include <ESAT\core\GPU.h>
#include <ESAT\core\Materials\Material.h>
#include <vector>
#include <ESAT\core\Texture.h>


namespace ESAT {
namespace core {

namespace Materials
{
	class Material;
}

enum UniformType
{
	UT_Color,
	UT_Color2,

};

class UniformBlock : public Referenced {

	private:

	ref_ptr<Materials::Material> material_;
	scoped_ptr<UniformBlockIndex> U_data;
	ref_ptr<Texture> tex;

	int8 offset_counter;
	//char *storage[];
	std::vector<float>storage;

	//int isCompatible(UniformType uniform,float *value);
	void isCompatible(const char * name,float *value);

	public:

		
	UniformBlock();
	~UniformBlock();


	void InitUniform(Materials::Material *mat,Texture * tex_ = 0);
	void Set(const char * uniform_name, float* value);

	friend class Drawable;
	friend class GPU;

	};

}
}
#endif
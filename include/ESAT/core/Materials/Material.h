#ifndef _MATERIAL_H__
#define _MATERIAL_H__

#include "ESAT\core\type_defines.h"
#include <ESAT\core\Ptr\Scoped_ptr.h>
#include <ESAT\core\Ptr\Referenced.h>
#include <ESAT\core\Geometry.h>


namespace ESAT {
namespace core {
	
class AttributeInfo;

namespace Materials {

	enum ShaderType {
	ST_Vertex,
	ST_Fragment,
	};
	
	
class Material : public Referenced {

private:

	scoped_ptr<AttributeInfo> attribute_info_material;

protected:
~Material();

public:

Material();


virtual void initMaterial(int shader_num,ShaderType st[],const char*shader_source[]);
virtual void setInfoMaterial();
virtual void destroyMaterial();

//virtual void Draw(ESAT::core::Geometry * geo);

friend class Material_01;
friend class Drawable;
friend class UniformBlock;

};

}
}
}
#endif
#ifndef _MATERIAL_SHADOW_H__
#define _MATERIAL_SHADOW_H__

#include "Material.h"

namespace ESAT {
namespace core {
namespace Materials {

	class Material_Shadow : public Material {

public:

Material_Shadow();
~Material_Shadow();

void setData(bool shadowMapping);

};

}
}
}


#endif
#include <ESAT/core/Materials/Material_Specular.h>
#include <ESAT/core/Shaders/Fragment/FragmentShaderSpecular.h>
#include <ESAT/core/Shaders/Vertex/VertexShaderSpecular.h>

namespace ESAT {
namespace core {
namespace Materials {

	Material_Specular::Material_Specular():Material()
	{
	}

	Material_Specular::~Material_Specular(){}

	void Material_Specular::setData()
	{
		ShaderType types[2];
		types[0] = ST_Fragment;
		types[1] = ST_Vertex;
		const char *result[2];
		result[0] = fragment_shaderSpecular;
		result[1] = vertex_shaderSpecular;

		initMaterial(2,types,result);
	}
}
}
}
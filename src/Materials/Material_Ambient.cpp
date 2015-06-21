#include <ESAT/core/Materials/Material_Ambient.h>
#include <ESAT/core/Shaders/Fragment/FragmentShaderAmbient.h>
#include <ESAT/core/Shaders/Vertex/VertexShaderAmbient.h>

namespace ESAT {
namespace core {
namespace Materials {

	Material_Ambient::Material_Ambient():Material()
	{
	}

	Material_Ambient::~Material_Ambient(){}

	void Material_Ambient::setData()
	{
		ShaderType types[2];
		types[0] = ST_Fragment;
		types[1] = ST_Vertex;
		const char *result[2];
		result[0] = fragment_shaderAmbient;
		result[1] = vertex_shaderAmbient;

		initMaterial(2,types,result);
	}
}
}
}
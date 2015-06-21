#include <ESAT/core/Materials/Material_Diffuse.h>
#include <ESAT/core/Shaders/Fragment/FragmentShaderDiffuse.h>
#include <ESAT/core/Shaders/Vertex/VertexShaderDiffuse.h>

namespace ESAT {
namespace core {
namespace Materials {

	Material_Diffuse::Material_Diffuse():Material()
	{
	}

	Material_Diffuse::~Material_Diffuse(){}

	void Material_Diffuse::setData()
	{
		ShaderType types[2];
		types[0] = ST_Fragment;
		types[1] = ST_Vertex;
		const char *result[2];
		result[0] = fragment_shaderDiffuse;
		result[1] = vertex_shaderDiffuse;

		initMaterial(2,types,result);
	}
}
}
}
#include "ESAT/core/Materials/Material_Shadow.h"
#include "ESAT/core/Materials/Material.h"
#include "ESAT\core\GPU.h"
#include <ESAT/core/Shaders/Vertex/VertexShaderShadow.h>
#include <ESAT/core/Shaders/Fragment/FragmentShaderShadow.h>

using namespace ESAT::core::Materials;


Material_Shadow::Material_Shadow():Material()
{
	//setData();
}

Material_Shadow::~Material_Shadow(){}

void Material_Shadow::setData(bool shadowMapping)
{
	ShaderType types[2];
	types[0] = ST_Fragment;
	types[1] = ST_Vertex;
	const char *result[2];
	if(shadowMapping == true)
	{
		result[0] = fragment_shaderShadow;
		result[1] = vertex_shaderShadow;
	}
	else
	{
		result[0] = fragment_shadow;
		result[1] = vertex_shadow;
	}
	initMaterial(2,types,result);
	
}
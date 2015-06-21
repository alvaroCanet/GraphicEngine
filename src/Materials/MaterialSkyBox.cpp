#include "ESAT/core/Materials/MaterialSkyBox.h"
#include "ESAT/core/Materials/Material.h"
#include "ESAT\core\GPU.h"
#include <ESAT/core/Shaders/Vertex/VertexShaderSkyBox.h>
#include <ESAT/core/Shaders/Fragment/FragmentShaderSkyBox.h>

using namespace ESAT::core::Materials;


Material_SkyBox::Material_SkyBox():Material()
{
	//setData();
}

Material_SkyBox::~Material_SkyBox(){}

void Material_SkyBox::setData()
{
	ShaderType types[2];
	types[0] = ST_Fragment;
	types[1] = ST_Vertex;
	const char *result[2];
	
	result[0] = fragment_shader;
	result[1] = vertex_shader;
	
	initMaterial(2,types,result);
	
}
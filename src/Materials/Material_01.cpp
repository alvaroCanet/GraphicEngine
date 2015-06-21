#include "ESAT/core/Materials/Material_01.h"
#include "ESAT/core/Materials/Material.h"
#include "ESAT\core\GPU.h"
#include <ESAT/core/Shaders/Vertex/VertexShader.h>
#include <ESAT/core/Shaders/Fragment/FragmentShader.h>

using namespace ESAT::core::Materials;


Material_01::Material_01():Material()
{
	//setData();
}

Material_01::~Material_01(){}

void Material_01::setData()
{
	ShaderType types[2];
	types[0] = ST_Fragment;
	types[1] = ST_Vertex;
	const char *result[2];
	result[0] = fragment_shader;
	result[1] = vertex_shader;

	initMaterial(2,types,result);
	
}
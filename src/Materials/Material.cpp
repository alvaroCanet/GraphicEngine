#include "ESAT\core\Materials/Material.h"
#include <ESAT/core/Shaders/Fragment/FragmentShaderSimpleMaterial.h>
#include <ESAT/core/Shaders/Vertex/VertexShaderSimpleMaterial.h>
#include "ESAT\core\GPU.h"
#include <ESAT\core\AttributeInfo.h>

#include "GL\glew.h"

#include <stdlib.h>
#include <iostream>

using namespace ESAT::core::Materials;


Material::Material(){}

Material::~Material(){}

void Material::initMaterial(int shader_num,ShaderType st[],const char*shader_source[]) {

	attribute_info_material.alloc();
	GPU::Instance()->CreateMaterial(shader_num,(int*)st,shader_source,attribute_info_material.get_ptr());
	
}


void Material::setInfoMaterial() {

	ShaderType types[2];
	types[0] = ST_Fragment;
	types[1] = ST_Vertex;
	const char *result[2];
	result[0] = fragment_shaderSimpleMaterial;
	result[1] = vertex_shaderSimpleMaterial;

	initMaterial(2,types,result);
	
}



void Material::destroyMaterial() {




}



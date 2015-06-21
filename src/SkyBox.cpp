#include <ESAT\core\SkyBox.h>
#include <ESAT\core\Tools\LoadTextures.h>

namespace ESAT {
namespace core {

static const GLenum types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,};

CSkybox::CSkybox(){}

CSkybox::~CSkybox(){}

void CSkybox::Init()
{
	for(int i = 0; i<6 ;i++)
	{
		tTextures[i].alloc();
	}
	SkyBoxDrawable.alloc();
	SkyGeo.alloc();
	SkyUniformBlock.alloc();
	SkyMaterial.alloc();
}

void CSkybox::loadSkybox(std::string a_sDirectory, std::string a_sFront, std::string a_sBack, std::string a_sLeft, std::string a_sRight, std::string a_sTop, std::string a_sBottom) 
{ 
	tTextures[0]->Init(&(a_sDirectory + a_sFront));
	tTextures[0]->texture_data.my_texture = stbi_load(tTextures[0]->texture_data.tex.c_str(),
													 &tTextures[0]->texture_data.width_,
													 &tTextures[0]->texture_data.height_,
													 &tTextures[0]->texture_data.components,
													 0);
	tTextures[1]->Init(&(a_sDirectory + a_sBack));
	tTextures[1]->texture_data.my_texture = stbi_load(tTextures[1]->texture_data.tex.c_str(),
													 &tTextures[1]->texture_data.width_,
													 &tTextures[1]->texture_data.height_,
													 &tTextures[1]->texture_data.components,
													 0);
	tTextures[2]->Init(&(a_sDirectory + a_sLeft));
	tTextures[2]->texture_data.my_texture = stbi_load(tTextures[2]->texture_data.tex.c_str(),
													 &tTextures[2]->texture_data.width_,
													 &tTextures[2]->texture_data.height_,
													 &tTextures[2]->texture_data.components,
													 0);
	
	tTextures[3]->Init(&(a_sDirectory + a_sRight));
	tTextures[3]->texture_data.my_texture = stbi_load(tTextures[3]->texture_data.tex.c_str(),
													 &tTextures[3]->texture_data.width_,
													 &tTextures[3]->texture_data.height_,
													 &tTextures[3]->texture_data.components,
													 0);
	tTextures[4]->Init(&(a_sDirectory + a_sTop));
	tTextures[4]->texture_data.my_texture = stbi_load(tTextures[4]->texture_data.tex.c_str(),
													 &tTextures[4]->texture_data.width_,
													 &tTextures[4]->texture_data.height_,
													 &tTextures[4]->texture_data.components,
													 0);
	
	tTextures[5]->Init(&(a_sDirectory + a_sBottom));
	tTextures[5]->texture_data.my_texture = stbi_load(tTextures[5]->texture_data.tex.c_str(),
													 &tTextures[5]->texture_data.width_,
													 &tTextures[5]->texture_data.height_,
													 &tTextures[5]->texture_data.components,
													 0);


	glGenTextures(1,&tTextures[0]->texture_data.id_texture_);
	glBindTexture(GL_TEXTURE_CUBE_MAP,((tTextures[0]->texture_data.id_texture_)));
	
	for (unsigned int i = 0 ; i < 6; i++)
	{
		glTexImage2D(types[i], 0, GL_RGBA, 
		tTextures[0]->texture_data.width_,tTextures[0]->texture_data.height_,
		0, GL_RGB, GL_UNSIGNED_BYTE,tTextures[i]->texture_data.my_texture);
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	SkyGeo->createCube(5);
	SkyMaterial->setData();
	
	SkyUniformBlock->InitUniform(SkyMaterial.get());

	SkyBoxDrawable->CreateDrawable(SkyGeo.get(),SkyUniformBlock.get());

}

void CSkybox::renderSkybox(mat4 * view, mat4*proj)
{
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB,tTextures[0]->texture_data.id_texture_);
	float aux = 0;
	SkyUniformBlock->Set("gCubemapTexture",&aux);
	SkyBoxDrawable->Draw(view,proj);
}
}
}
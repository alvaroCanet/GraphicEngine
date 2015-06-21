#include <ESAT\core\Texture.h>
//#include <ESAT\core\Tools\LoadTextures.h>


namespace ESAT {
namespace core {

	Texture::Texture()
	{
		texture_data.tex = "0";
	}

	Texture::~Texture(){}
	
	void Texture::Init(std::string *image)
	{
		texture_data.tex = *image;
	}

	void Texture::LoadImage()
	{
		//texture_data.my_texture = stbi_load(texture_data.tex.c_str(),&texture_data.width_,&texture_data.height_,&texture_data.components,0);
		
		if(texture_data.my_texture!=NULL)
		{
			texture_data.type_ = PDT_UNSIGNED_BYTE;
			texture_data.format_ = (Format) texture_data.components;
			texture_data.internal_format_ = (InternalFormat) texture_data.components;
		}
		else
		{
			fprintf(stderr,"\n********************************************************************** \n********Error , textura no valida!********\n**********************************************************************");
		}

	}

	void Texture::LoadTexture()
	{
		GPU::Instance()->CreateTexture(&texture_data.id_texture_,texture_data.internal_format_,texture_data.width_,texture_data.height_,texture_data.format_,texture_data.type_,texture_data.my_texture);
	}

	void Texture::ActiveUniformTexture(const char * uniform_name)
	{
		
	}

	void Texture::CreateRenderToTexture()
	{
		GPU::Instance()->RenderToTexture(&texture_data.FramebufferId,&texture_data.id_texture_,&texture_data.DepthBuffer);
	}

	void Texture::CreateRenderDepthToTexture()
	{
		GPU::Instance()->RenderDepthToTexture(&texture_data.FramebufferId,&texture_data.id_texture_);
	}

}
}
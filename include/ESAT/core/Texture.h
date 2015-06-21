#ifndef _TEXTURE_H__
#define _TEXTURE_H__
#include <ESAT\core\GPU.h>
#include <string>

namespace ESAT {
namespace core {

enum ComponentsType
{
	R,
	RG,
	RGB,
	RGBA,
};

struct TextureInfo
{
	std::string tex;
	unsigned int  id_texture_;
	InternalFormat internal_format_;
	int width_;
	int height_;
	Format format_;
	PixelDataType type_;
	int components;
	unsigned char *my_texture;

	//rendertotexture
	uint32 FramebufferId;
	//uint32 RenderTexture;
	uint32 DepthBuffer;
	
};

//unsigned int * id,InternalFormat *internal_format,int * w, int *h, Format *format,PixelDataType *type, void * data)


	class Texture : public Referenced
	{
	public:
		void Init(std::string *image);
		void LoadImage();
		void LoadTexture();
		void ActiveUniformTexture(const char* uniform_name);
		void CreateRenderToTexture();
		void CreateRenderDepthToTexture();
		Texture();
		~Texture();
		TextureInfo texture_data;
	private:
		
		
		
		friend class UniformBlock;
		friend class Drawable;
		friend class Camera;
	};

}
}
#endif
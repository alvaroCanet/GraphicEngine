#ifndef _GPU_H__
#define _GPU_H__

#include <ESAT/core/Ptr/scoped_ptr.h>
#include <ESAT\core\type_defines.h>
#include <ESAT\core\AttributeInfo.h>
#include <ESAT\core\Geometry.h>
//#include <ESAT\core\UniformBlock.h>

#include "glm/glm.hpp"   // --> Mathematical functions
#include <glm/gtc/type_ptr.hpp>

#include "GL\glew.h"

namespace ESAT {
namespace core {
	class UniformBlock;
	namespace Materials
	{
		class Material;
		class Material_01;
	}


	enum ShaderType {
	ST_Vertex,
	ST_Fragment,
	};
	
	enum InternalFormat {
      IF_INVALID,
	  IF_R,
      IF_RG,
      IF_RGB,
      IF_RGBA,
	  IF_DEPTH,
	};

	enum Format {
	 F_INVALID,
	 F_RED, 
	 F_RG, 
	 F_RGB, 
	 F_RGBA,
	 F_DEPTH,
	 F_BGR,
	 F_BGRA,
	
	};
	
	enum PixelDataType {
		 PDT_INVALID,
		 PDT_UNSIGNED_BYTE,
		 PDT_BYTE,
		 PDT_UNSIGNED_SHORT,
		 PDT_SHORT,
		 PDT_UNSIGNED_INT,
		 PDT_INT, 
		 PDT_FLOAT,
	};

class data;

class GPU
{

public:

	
	static GPU* Instance();
	

private:

	 static GPU* gpu_instance;
	 char attribute_names_array[32][50];//AttributesName.
	 

	 static void DestroyGPU();

	  /*Buffers*/
	  void InicializationBuffer(data *dat);
	  void SetData(void *data_,uint32 size,uint32 offset,data *dat,uint32 typeofBuffer);
	  void DestroyBuffer(data *dat);
	  /*Shader/Material*/
	  void CreateMaterial(int shader_num,int st[],const char*shader_source[],AttributeInfo *attributeinfo);
	  void EnableAttribPointer(int32 index,uint32 size,int32 stride,int32 offset,Geometry * geo);
	  /*Draw*/
	  void UseProgram(uint32 id_program);
	  void Draw(uint32 num,uint32 vertexArray_id,uint32 elementArray_id);
	  /*Uniform*/
	  void GetUniforms(uint32 id_program,UniformBlock *uniform_block_);
	  uint32 GetUniformLocation(char *uniform,uint32 id_program);
	  void LocalMatrixToShader(unsigned int id,glm::mat4 *model);
	  /*Texture*/
	  GLenum TransformFormatGL(Format *format);
	  GLenum TranstormInternalFormatGL(InternalFormat *inter_format);
	  GLenum TransformPixelDataTypeGL(PixelDataType *data_type);
	  int32 GLElementsSize(GLenum enum_);
	  int32 GLElementsType(GLenum enum_);
	  int32 AttributeID(const char* attribname);

	  void CreateTexture(unsigned int *id,InternalFormat internal_format,int w, int h, Format format,PixelDataType type,void * data);
	  void UpdateTexture(unsigned int * id);
	  void ActiveTexture(uint32 id_/*const char * name,uint32 id_program*/);
	  void UpdateModelViewUniform(unsigned int id,glm::mat4 *view,glm::mat4 *proj);
	  /*RendertoTexture*/
	  void RenderToTexture(uint32 *frame_buffer_id,uint32 *rendertex,uint32 *depth_buffer);
	  void BindOnBuffer(uint32 *idFrameBuffer,bool depth = false);
	  void BindOnScreen(bool depth = false);
	  /*RenderDepthToTexture*/
	  bool RenderDepthToTexture(uint32 *frame_buffer_id,uint32 * depthTex);
	  
protected:

	GPU();
    GPU(const GPU & ) ;
    GPU &operator= (const GPU & ) ;

	friend class Buffer;
	friend class Materials::Material;
	friend class Materials::Material_01;
	friend class AttibuteInfo;
	friend class Drawable;
	friend class UniformBlock;
	friend class Texture;
	friend class Camera;
	friend class CSkybox;
	//friend class CSkybox;
	

};

}
}

#endif
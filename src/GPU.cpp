#include "ESAT\core\GPU.h"
#include "ESAT\core\data.h"
#include <ESAT\core\Tools\Ptr_Tools.h>
#include <ESAT\core\Buffer.h>
#include <ESAT\core\Geometry.h>
#include <ESAT\core\Texture.h>
#include <ESAT\core\UniformBlock.h>
//#include "ESAT\core\Materials\Material.h"

#include <stdlib.h>
#include <iostream>


using std::cout;
using std::endl;


namespace ESAT {
namespace core {

GPU* GPU::gpu_instance = 0;// Inicializar el puntero

GPU* GPU::Instance ()
{
  if (gpu_instance == 0)  // ¿Es la primera llamada?
  {
    gpu_instance = new GPU(); // Creamos la instancia
	atexit(&DestroyGPU);
  }
  return gpu_instance; // Retornamos la dirección de la instancia
}

GPU::GPU()
{
  //... Realizar inicializaciones necesarias de la instancia
}

void GPU::DestroyGPU()
{
	if(gpu_instance != 0) delete gpu_instance;
}

void GPU::InicializationBuffer(data *dat)
{
	glGenBuffers(1,&dat->id_);
	glBindBuffer(GL_ARRAY_BUFFER,dat->id_);
	glBufferData(GL_ARRAY_BUFFER,dat->size_,NULL,GL_STATIC_DRAW);
	 
}

void GPU::SetData(void *data_,uint32 size,uint32 offset,data *dat,uint32 typeofBuffer)
{
	//if(size+offset<=dat->size_)
	//{
	switch(typeofBuffer)
	{
		case 0: glBindBuffer(GL_ARRAY_BUFFER,dat->id_); glBufferSubData(GL_ARRAY_BUFFER,offset,size,data_);break;
		case 1: glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,dat->id_); glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,offset,size,data_);break;
	}
		
	//}
	
}


void GPU::DestroyBuffer(data *dat)
{
	glDeleteBuffers(1,&dat->id_);	
}


int32 GPU::GLElementsSize(GLenum enum_)
{
	switch (enum_)
	{
		case GL_INT:case GL_FLOAT:case GL_UNSIGNED_INT: return 1;
		case GL_SAMPLER_2D:case GL_SAMPLER_CUBE: return 1;
		case GL_FLOAT_VEC2: return 2;
		case GL_FLOAT_VEC3: return 3;
		case GL_FLOAT_VEC4: return 4;
		case GL_FLOAT_MAT4: return 16;
	}
}


int32 GPU::GLElementsType(GLenum enum_)
{
	switch (enum_)
	{
		case GL_INT:return 1;
		case GL_FLOAT: return 10;
		case GL_UNSIGNED_INT: return 100;
		case GL_SAMPLER_2D: return 11;
		case GL_SAMPLER_CUBE: return 12;
		case GL_FLOAT_VEC2: return 2;
		case GL_FLOAT_VEC3: return 3;
		case GL_FLOAT_VEC4: return 4;
		case GL_FLOAT_MAT4: return 16;
	}
}

int32 GPU::AttributeID(const char* attribname)
{
	if(strcmp("atrib_position",attribname)==0)
	{
		return 1;
	}
	else if(strcmp("atrib_color",attribname)==0)
	{
		return 2;
	}
	else if(strcmp("atrib_uv",attribname)==0)
	{
		return 3;
	}
}

void GPU::CreateMaterial(int shader_num,int st[],const char*shader_source[],AttributeInfo *attributeinfo)
{
	//Create Program
	uint32 id_program = glCreateProgram();
	if (id_program == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
	}

	//Create Shader,Load Source , Compile shader and Attach Shader.
	for(int i = 0; i< shader_num;++i)
	{
		uint32 shader_id = 0;
		switch(st[i])
		{
			case 0 : shader_id = glCreateShader(GL_VERTEX_SHADER);break;
			case 1 : shader_id = glCreateShader(GL_FRAGMENT_SHADER);break;
			default: shader_id = glCreateShader(GL_VERTEX_SHADER);break;
		}

		glShaderSource(shader_id,1,&shader_source[i],NULL);

		glCompileShader(shader_id);
	
		GLint error;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &error);//Compruebo el estado de compilacion del fragment
		if (!error) {
			 GLchar InfoLog[1024];
			 glGetShaderInfoLog(shader_id, 1024, NULL, InfoLog);
			 fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader_id, InfoLog);//En caso de que haya algun error se muestra por pantalla
		}

		glAttachShader(id_program,shader_id);

	}
	//Linker and use Program
	glLinkProgram(id_program);
	
	//Attributes
	#pragma region Attributes_con_glgetactiveattrib
	/*GLint size;
	GLenum type;
	GLchar attrib_name[50],aux[100];
	GLint active_attribs;
	float offset_ = 0;
	glGetProgramiv(id_program, GL_ACTIVE_ATTRIBUTES, &active_attribs);
	attributeinfo->attrib_num = active_attribs;
	for (int index = 0; index < active_attribs; index++)
	{
		attributeinfo->program = id_program;
		attributeinfo->ActiveAttribute(index + 1);
		glGetActiveAttrib(id_program,index,50,NULL, &size, &type,&attributeinfo->attrib_name[index][0]);
		strcpy(aux,attributeinfo->attrib_name[index]);
		attributeinfo->index_[AttributeID(aux)-1] = glGetAttribLocation(id_program,aux) ;
	}*/

	#pragma endregion 	

	#pragma region Attributes_sin_glgetactiveattrib
	//Array bidimensional con los nombres de los posibles atributos que tengo.
	memset(attribute_names_array,'\0',sizeof(attribute_names_array));
	strcpy(&attribute_names_array[0][0],"atrib_position");
	strcpy(&attribute_names_array[1][0],"atrib_color");
	strcpy(&attribute_names_array[2][0],"atrib_uv");
	strcpy(&attribute_names_array[3][0],"atrib_normal");
	
	//Calculo cuantos atributos de un maximo de 32 puedo utilizar.Podria poner directamente el numero de atrib. que tengo en el array anterior. 
	int sizeAttributes = 0;
	for(int i = 0 ; i<32 && attribute_names_array[sizeAttributes][i]!='\0';++i)
	{
		sizeAttributes++;
	}

	for(int i = 0 ; i<sizeAttributes;++i)
	{   //getlocation on shader
		int atributte_array  = glGetAttribLocation(id_program,attribute_names_array[i]);
		if(atributte_array != -1)
		{   //Si se encuentra en el shader se activa de lo contrario no se hace y se muestra que no se ha encontrado.
			attributeinfo->program = id_program;
			attributeinfo->ActiveAttribute(i+1);
			attributeinfo->index_[i] = atributte_array;	 
		}
		else 
		{
			attributeinfo->index_[i] = atributte_array;
			fprintf(stderr,"-Attribute %s not found in program %d\n",attribute_names_array[i],id_program);
		}
	}
	#pragma endregion 


}

void GPU::EnableAttribPointer(int32 index,uint32 size,int32 stride,int32 offset,Geometry *geo)
{
	if(index!=-1)
	{
		glEnableVertexAttribArray(index);
		glBindBuffer(GL_ARRAY_BUFFER, geo->geometryArray.get_ptr()->getBufferData()->id_);
		glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE,stride,(void*)(offset*sizeof(float)));
	}
}

void GPU::UseProgram(uint32 id_program){

	glUseProgram(id_program);

}

void GPU::Draw(uint32 num,uint32 vertexArray_id,uint32 elementArray_id){

	glBindBuffer(GL_ARRAY_BUFFER,vertexArray_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elementArray_id);
	//glDrawArrays(GL_TRIANGLE_STRIP,0,num);
	glDrawElements(GL_TRIANGLES,num,GL_UNSIGNED_INT,0);
}

void GPU::GetUniforms(uint32 id_program,UniformBlock *uniform_block_)
{
	int iterator,offset=0;
	GLenum type;
	GLint size_;
	char name[80];
	std::string aux;
	GLint active_uniforms;
	glGetProgramiv(id_program,GL_ACTIVE_UNIFORMS, &active_uniforms);
	for(int i = 0;i<active_uniforms;++i)
	{
		iterator = 0;
		glGetActiveUniform(id_program,i,50,NULL,&size_,&type,name);
		aux = name;
		if((strcmp(aux.c_str(),"u_model")==0) || (strcmp(aux.c_str(),"u_projection")==0) || 
		   (strcmp(aux.c_str(),"u_view")==0)  || (strcmp(aux.c_str(),"gSampler")==0))
		{
			
			iterator++;
		}
		else
		{
			for(int j = 0;j<uniform_block_->U_data->Uniform_data.U_name.size();++j)
			{
				if(aux == uniform_block_->U_data->Uniform_data.U_name[j])
				{
					iterator++;
				}
			}
		}
		if(iterator==0)
		{
			uniform_block_->U_data->Uniform_data.U_index.push_back(glGetUniformLocation(id_program,aux.c_str()));
			uniform_block_->U_data->Uniform_data.U_name.push_back(aux);
			uniform_block_->U_data->Uniform_data.U_size.push_back(GLElementsSize(type));
			uniform_block_->U_data->Uniform_data.U_type.push_back(GLElementsType(type));
			uniform_block_->U_data->Uniform_data.U_active.push_back(false);
			uniform_block_->U_data->Uniform_data.U_offset.push_back(offset);
			offset+=GLElementsSize(type);
		}	
	}

}

uint32 GPU::GetUniformLocation(char *uniform,uint32 id_program)
{
	return glGetUniformLocation(id_program,uniform);
}

void GPU::LocalMatrixToShader(unsigned int id,glm::mat4 *model)
{
	glUniformMatrix4fv(id,1,GL_FALSE,(const GLfloat*) model);
}

//Texture
GLenum GPU::TransformFormatGL(Format *format)
{
	switch((*format)) 
	{
		case F_RED:   return GL_RED;
		case F_RG:    return GL_RG;
		case F_RGB:   return GL_RGB;
		case F_BGR:   return GL_BGR;
		case F_RGBA:  return GL_RGBA;
		case F_BGRA:  return GL_BGRA;
		case F_DEPTH: return GL_DEPTH;
	}
}

GLenum GPU::TranstormInternalFormatGL(InternalFormat *inter_format)
{
	switch ((*inter_format))
	{
		case IF_R:	   return GL_RED; 
		case IF_RG:    return GL_RG; 
		case IF_RGB:   return GL_RGB; 
		case IF_RGBA:  return GL_RGBA;
		case IF_DEPTH: return GL_DEPTH;
	}
}

GLenum GPU::TransformPixelDataTypeGL(PixelDataType *data_type)
{
	switch ((*data_type))
	{
	case PDT_UNSIGNED_BYTE :  return GL_UNSIGNED_BYTE;
	case PDT_UNSIGNED_SHORT : return GL_UNSIGNED_SHORT;
	case PDT_UNSIGNED_INT :   return GL_UNSIGNED_INT;
	case PDT_FLOAT :          return GL_FLOAT;
	case PDT_BYTE :           return GL_BYTE;
	case PDT_SHORT:           return GL_SHORT;
	case PDT_INT :            return GL_INT;
	}
}

void GPU::CreateTexture(unsigned int *id,InternalFormat internal_format,int w, int h, Format format,PixelDataType type, void * data)
{
	glGenTextures(1,id);
	glBindTexture(GL_TEXTURE_2D,(*id));
	glTexImage2D(GL_TEXTURE_2D,0,TransformFormatGL(&format),w,h,0,TransformFormatGL(&format),TransformPixelDataTypeGL(&type),data);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	

}


void GPU::ActiveTexture(uint32 id_)
{
	//uint32 id_ = glGetUniformLocation(id_program,name);
	//glUniform1i(id_,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,id_);

}

void GPU::UpdateModelViewUniform(unsigned int id,glm::mat4 *view,glm::mat4 *proj)
{
	uint32 view_location = GetUniformLocation("u_view",id);
	uint32 projection_location = GetUniformLocation("u_projection",id);
	glUniformMatrix4fv(view_location,1,GL_FALSE,(GLfloat*)view);
	glUniformMatrix4fv(projection_location,1,GL_FALSE,(GLfloat*)proj);

}

void GPU::RenderToTexture(uint32 *frame_buffer_id, uint32 *rendertex, uint32 *depth_buffer)
{
	glGenTextures(1, rendertex);
	glBindTexture(GL_TEXTURE_2D, (*rendertex));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//NULL means reserve texture memory, but texels are undefined
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//-------------------------
	glGenFramebuffers(1, frame_buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, (*frame_buffer_id));
	//Attach 2D texture to this FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,(*rendertex), 0);
	//-------------------------
	glGenRenderbuffers(1, depth_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, (*depth_buffer));
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 800, 600);
	//-------------------------
	//Attach depth buffer to FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, (*depth_buffer));
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Fail");
}

bool GPU::RenderDepthToTexture(uint32 *frame_buffer_id,uint32 * depthTex)
{
	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	 glGenTextures(1, depthTex);
	 glBindTexture(GL_TEXTURE_2D, *depthTex);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	 glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 800, 600, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	
	 // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	 glGenFramebuffers(1, frame_buffer_id);
	 glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id);
 
	 glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *depthTex, 0);
 
	 glDrawBuffer(GL_NONE); // No color buffer is drawn to.
 
	 // Always check that our framebuffer is ok
	 if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 return false;
}

void GPU::BindOnBuffer(uint32 *idFrameBuffer,bool depth)
{
	if(depth == false)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, (*idFrameBuffer));
	}
	else
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, (*idFrameBuffer));
	}
}

void GPU::BindOnScreen(bool depth)
{
	if(depth == false)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
}

}
}
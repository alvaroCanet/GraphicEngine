#include <ESAT\core\Drawable.h>
#include <ESAT\core\Materials\Material.h>
#include <ESAT\core\Materials\Material_Shadow.h>
#include <ESAT\core\Buffer.h>
#include <ESAT\core\Geometry.h>
#include "ESAT\core\data.h"
#include <ESAT\core\AttributeInfo.h>
#include <ESAT\core\GPU.h>
#include <ESAT\core\Texture.h>
#include "GL\glew.h"

#include <iostream>

namespace ESAT {
namespace core {

	Drawable::Drawable() : Node(TP_Drawable)
	{ 
		compatible = false;
	}

	Drawable::~Drawable(){}

	void Drawable::CreateDrawable(Geometry *geo,UniformBlock *uniform)
	{
		
		compatible = uniform->material_->attribute_info_material->IsCompatible(geo->attribute_info_geometry->getAttributeMask());

		if(compatible == true)
		{
			geo_ = geo;
			uniform_block = uniform;
		}

		/*//Shadow
		uniform_block_shadow.alloc();
		ref_ptr<Materials::Material_Shadow> mat_shadow;
		mat_shadow.alloc();
		mat_shadow->setData(true);
		uniform_block_shadow->InitUniform(mat_shadow.get());*/
		

	}


	void Drawable::Draw(mat4 *view,mat4 *proj) 
	{
		if(compatible == true)
		 {     
			//Program
			 GPU::Instance()->UseProgram(uniform_block->material_->attribute_info_material->program);
			//Enable Atributes
			for(int i = 0;i<geo_->attribute_info_geometry->attrib_num;++i)
			{
				GPU::Instance()->EnableAttribPointer(uniform_block->material_->attribute_info_material->index_[i]
													,geo_->attribute_info_geometry->size_[i]
													,geo_->attribute_info_geometry->stride
													,geo_->attribute_info_geometry->offset[i+1],geo_.get());
			}
			
			//Uniform
			/*GPU::Instance()->GetUniforms(uniform_block->material_->attribute_info_material->program,uniform_block.get());*/
			for(int i = 0;i<uniform_block->U_data->getUniformData()->U_index.size();++i)
			{
				if(uniform_block->U_data->getUniformData()->U_active[i] == true)
				{
					switch(uniform_block->U_data->getUniformData()->U_type[i])
					{
						case 10: glUniform1f(uniform_block->U_data->getUniformData()->U_index[i],uniform_block->storage[uniform_block->U_data->getUniformData()->U_offset[i]]);break;
						case 3: glUniform3fv(uniform_block->U_data->getUniformData()->U_index[i],1,&uniform_block->storage[uniform_block->U_data->getUniformData()->U_offset[i]]);break;
						case 12 : glUniform1i(uniform_block->U_data->getUniformData()->U_index[i],uniform_block->storage[uniform_block->U_data->getUniformData()->U_offset[i]]);break;
						//case 4:	glUniform4fv(uniform_block->U_data->getUniformData()->U_index[i],1,&uniform_block->storage[0]);break;
					}
				}
			}
			unsigned int id_ = GPU::Instance()->GetUniformLocation("u_model",uniform_block->material_->attribute_info_material->program);
			
			GPU::Instance()->LocalMatrixToShader(id_,&ModelMatrix);

			if(uniform_block->tex.get() != 0)
			{
				GPU::Instance()->ActiveTexture(uniform_block->tex->texture_data.id_texture_);
			}
			
			GPU::Instance()->UpdateModelViewUniform(uniform_block->material_->attribute_info_material->program,view,proj);
			GPU::Instance()->Draw(geo_->relationalArray->getBufferData()->num_elements_,geo_.get()->geometryArray.get_ptr()->getBufferData()->id_,geo_->relationalArray->getBufferData()->id_);
		}
	}

	void Drawable::DrawWithShadow(mat4 *view,mat4 *proj,vec3 eyePos,UniformBlock *uniformShad) 
	{
			if(compatible == true)
			{     
				ref_ptr<UniformBlock>  uniform_block_;
				uniform_block_ = uniformShad;
				
				/*float eyePos_[3];
				eyePos_[0] =eyePos.x ;
				eyePos_[1] =eyePos.y ;
				eyePos_[2] =eyePos.z ;
				uniform_block_->Set("eye_Pos",eyePos_);*/

				View = (*view);
				Projection = (*proj);
				oldModelMatrix = ModelMatrix;
				//Program
				 GPU::Instance()->UseProgram(uniform_block_->material_->attribute_info_material->program);
				//Enable Atributes
				for(int i = 0;i<geo_->attribute_info_geometry->attrib_num;++i)
				{
					GPU::Instance()->EnableAttribPointer(uniform_block_->material_->attribute_info_material->index_[i]
														,geo_->attribute_info_geometry->size_[i]
														,geo_->attribute_info_geometry->stride
														,geo_->attribute_info_geometry->offset[i+1],geo_.get());
				}
			
				//Uniform
				/*GPU::Instance()->GetUniforms(uniform_block->material_->attribute_info_material->program,uniform_block.get());*/
				for(int i = 0;i<uniform_block_->U_data->getUniformData()->U_index.size();++i)
				{
					if(uniform_block_->U_data->getUniformData()->U_active[i] == true)
					{
						switch(uniform_block_->U_data->getUniformData()->U_type[i])
						{
							case 10: glUniform1f(uniform_block_->U_data->getUniformData()->U_index[i],uniform_block_->storage[uniform_block_->U_data->getUniformData()->U_offset[i]]);break;
							case 3: glUniform3fv(uniform_block_->U_data->getUniformData()->U_index[i],1,&uniform_block_->storage[uniform_block_->U_data->getUniformData()->U_offset[i]]);break;
							//case 4:	glUniform4fv(uniform_block->U_data->getUniformData()->U_index[i],1,&uniform_block->storage[0]);break;
						}
					}
				}
				unsigned int id_ = GPU::Instance()->GetUniformLocation("u_model",uniform_block_->material_->attribute_info_material->program);
			
				GPU::Instance()->LocalMatrixToShader(id_,&ModelMatrix);

				if(uniform_block_->tex.get() != 0)
				{
					GPU::Instance()->ActiveTexture(uniform_block_->tex->texture_data.id_texture_);
				}
				GPU::Instance()->UpdateModelViewUniform(uniform_block_->material_->attribute_info_material->program,view,proj);
				GPU::Instance()->Draw(geo_->relationalArray->getBufferData()->num_elements_,geo_.get()->geometryArray.get_ptr()->getBufferData()->id_,geo_->relationalArray->getBufferData()->id_);
		

			}
	}


	void Drawable::DrawShadowFinal(mat4 *view,mat4 *proj,UniformBlock *uniformShad,Texture * tex_) 
	{
			if(compatible == true)
			{     
				
				ref_ptr<UniformBlock>  uniform_block_;
				uniform_block_ = uniformShad;
				//uint32 location_texture = GPU::Instance()->GetUniformLocation("gShadowMap",uniform_block->material_->attribute_info_material->program);
				float aux = 0;//(float)tex_->texture_data.id_texture_;
				uniform_block_->Set("gShadowMap",&aux);

				View = glm::transpose(View);
				Projection = glm::transpose(Projection);
				oldModelMatrix = glm::transpose(oldModelMatrix);
				//glm::value_ptr(ModelViewProjection);
				float *auxiliar = glm::value_ptr(oldModelMatrix);
				float *auxiliar2 = glm::value_ptr(View);
				float *auxiliar3 = glm::value_ptr(Projection);

				/*for(int i = 1; i<17;i++)
				{
					printf("%f    ",auxiliar[i-1]);
					if(i%4 == 0)
					{
						printf("\n");
					}
				}
				printf("\n\n\n\n\n");
				system("pause");*/

				/*for(int i = 1; i<17;i++)
				{
					printf("%f    ",auxiliar3[i-1]);
					if(i%4 == 0)
					{
						printf("\n");
					}
				}
				system("pause");*/
				uniform_block_->Set("ModelLight",auxiliar);
				uniform_block_->Set("ViewLight",auxiliar2);
				uniform_block_->Set("ProjLight",auxiliar3);

				//Program
				 GPU::Instance()->UseProgram(uniform_block_->material_->attribute_info_material->program);
				//Enable Atributes
				for(int i = 0;i<geo_->attribute_info_geometry->attrib_num;++i)
				{
					GPU::Instance()->EnableAttribPointer(uniform_block_->material_->attribute_info_material->index_[i]
														,geo_->attribute_info_geometry->size_[i]
														,geo_->attribute_info_geometry->stride
														,geo_->attribute_info_geometry->offset[i+1],geo_.get());
				}
			
				//Uniform
				/*GPU::Instance()->GetUniforms(uniform_block->material_->attribute_info_material->program,uniform_block.get());*/
				for(int i = 0;i<uniform_block_->U_data->getUniformData()->U_index.size();++i)
				{
					if(uniform_block_->U_data->getUniformData()->U_active[i] == true)
					{
						switch(uniform_block_->U_data->getUniformData()->U_type[i])
						{
							case 10: glUniform1f(uniform_block_->U_data->getUniformData()->U_index[i],uniform_block_->storage[uniform_block_->U_data->getUniformData()->U_offset[i]]);break;
							case 3: glUniform3fv(uniform_block_->U_data->getUniformData()->U_index[i],1,&uniform_block_->storage[uniform_block_->U_data->getUniformData()->U_offset[i]]);break;
						  //case 4:	glUniform4fv(uniform_block->U_data->getUniformData()->U_index[i],1,&uniform_block->storage[0]);break;
							case 16: glUniformMatrix4fv(uniform_block_->U_data->getUniformData()->U_index[i],1,GL_TRUE,&uniform_block_->storage[uniform_block_->U_data->getUniformData()->U_offset[i]]);break;
							case 11: glUniform1i(uniform_block_->U_data->getUniformData()->U_index[i],uniform_block_->storage[uniform_block_->U_data->getUniformData()->U_offset[i]]);break;
						}
					}
				}
				unsigned int id_ = GPU::Instance()->GetUniformLocation("u_model",uniform_block_->material_->attribute_info_material->program);
			
				GPU::Instance()->LocalMatrixToShader(id_,&ModelMatrix);

				if(uniform_block_->tex.get() != 0 )
				{
					GPU::Instance()->ActiveTexture(uniform_block_->tex->texture_data.id_texture_);
				}

				if( tex_ != NULL)
				{
					GPU::Instance()->ActiveTexture(tex_->texture_data.DepthBuffer);//texture_data.id_texture_
				}

				GPU::Instance()->UpdateModelViewUniform(uniform_block_->material_->attribute_info_material->program,view,proj);
				GPU::Instance()->Draw(geo_->relationalArray->getBufferData()->num_elements_,geo_.get()->geometryArray.get_ptr()->getBufferData()->id_,geo_->relationalArray->getBufferData()->id_);
		

			}
	}
}
}
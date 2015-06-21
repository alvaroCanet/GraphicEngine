#include <ESAT\core\UniformBlock.h>
#include <glm/glm.hpp>

namespace ESAT {
namespace core {

	UniformBlock::UniformBlock(){}
	
	UniformBlock::~UniformBlock(){}

	void UniformBlock::InitUniform(Materials::Material *mat,Texture * tex_)
	{
		U_data.alloc();
		//storage.reserve(100);
		storage.resize(100);
		offset_counter = 0;
		material_ = mat;
		if(tex_!=0)
		{
			tex = tex_;
			if (tex->texture_data.tex.c_str() != NULL)
			{
				tex->LoadImage();
				tex->LoadTexture();
			}
		}
		else
		{
			tex = 0;
		}
		GPU::Instance()->GetUniforms(material_->attribute_info_material->program,this);
	}

	void UniformBlock::Set(/*UniformType uniform*/const char * uniform_name , float* value)
	{
		isCompatible(uniform_name,value);
		/*{
			fprintf(stderr, "Error in uniform update.");
		}*/
	}

	void UniformBlock::isCompatible(/*UniformType uniform*/const char * name, float* value)
	{
		#pragma region control_uniforms
		/*if(uniform == UT_Color || uniform == UT_Color2)
		{
			int32 color;
			for(int i = 0; i<4; ++i)
			{
				if(i<3)
				{
					if(value[i]<0.0 || value[i]>1.0)
					{
						fprintf(stderr, "Uniform value is not compatible.");
						return -1;
					}

				}
				else
				{
					switch (uniform)
						{
							case ESAT::core::UT_Color:
								color = GPU::Instance()->GetUniformLocation("color",material_->attribute_info_material->program);
								U_data->getUniformData()->U_index.push_back(color);
								U_data->getUniformData()->U_name.push_back("color");
								U_data->getUniformData()->U_offset.push_back(offset_counter);
								if(value[i] != -1)
								{
									U_data->getUniformData()->U_size.push_back(4);
									storage.push_back(value[0]);
									storage.push_back(value[1]);
									storage.push_back(value[2]);
									storage.push_back(value[3]);
								}
								else
								{
									float aux[4] = {value[0],value[1],value[2],1.0};
									U_data->getUniformData()->U_size.push_back(4);
									storage.push_back(aux[0]);
									storage.push_back(aux[1]);
									storage.push_back(aux[2]);
									storage.push_back(aux[3]);
								}
								offset_counter+=4;
								break;
							case ESAT::core::UT_Color2:
								U_data->getUniformData()->U_name.push_back("color2");
								U_data->getUniformData()->U_index.push_back(GPU::Instance()->GetUniformLocation("color2",material_->attribute_info_material->program));
								U_data->getUniformData()->U_offset.push_back(offset_counter);
								if(value[i] != -1)
								{
									U_data->getUniformData()->U_size.push_back(4);
								}
								else
								{
									float aux[4] = {value[0],value[1],value[2],1.0};
									U_data->getUniformData()->U_size.push_back(4);
									storage.push_back(aux[0]);
									storage.push_back(aux[1]);
									storage.push_back(aux[2]);
									storage.push_back(aux[3]);
								}
								offset_counter+=4;
								break;
						}
						//fprintf(stderr, "Uniform value is not compatible.");
						return 0;
					
				}

			}

		}*/
		#pragma endregion
		
		int iter = 0;
		std::vector<float> aux;
		for(int i = 0;i<U_data->Uniform_data.U_name.size();++i)
		{
			if(strcmp(name,U_data->Uniform_data.U_name[i].c_str())==0)
			{
				U_data->Uniform_data.U_active.erase(U_data->Uniform_data.U_active.begin()+i);
				U_data->Uniform_data.U_active.insert(U_data->Uniform_data.U_active.begin()+i,true);
				for(int p = 0; p < U_data->Uniform_data.U_size[i];++p)
				{
					int offset_ = U_data->Uniform_data.U_offset[iter]+p;
					//storage.insert(storage.begin()+offset_,value[p]);
					float aux = value[p];
					storage[offset_] = value[p];
					//(U_data->Uniform_data.U_offset[iterator]+p),value[p]
					//storage.push_back(value[p]);
				}
			}
			aux.clear();
			iter++;
		}
	}


}
}

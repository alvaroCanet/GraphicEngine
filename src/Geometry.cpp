#include <vector>

#include "ESAT\core\Geometry.h"
#include "ESAT\core\Buffer.h"
#include "ESAT/core/Ptr/Scoped_ptr.h"
#include "ESAT\core\ObjLoader.h"


namespace ESAT {
namespace core {

	Geometry::Geometry(){}

	Geometry::~Geometry(){}

	void Geometry::createPlane(float32 x_,float32 y_,float32 z_,float32 width,float32 height,glm::vec3 color)
	{
		 float32 array_[] = {
			x_,y_,z_	,			color.x,color.y,color.z,	0.0,0.0,0.0,  0.0,1.0,0.0,
			x_, y_, z_ + height,	color.x,color.y,color.z,	1.0,0.0,0.0,  0.0,1.0,0.0,
			x_ + width, y_, z_,		color.x,color.y,color.z,	0.0,1.0,0.0,  0.0,1.0,0.0,
			x_+width, y_,z_+height, color.x,color.y,color.z,    1.0,1.0,0.0,  0.0,1.0,0.0,
		};

		 unsigned int relationalarray_[] = {
			 0,1,2,3,2,1
	    };

		 geometryArray.alloc();
		 relationalArray.alloc();
		 attribute_info_geometry = 0;
		 attribute_info_geometry.alloc();
		 geometryArray->init(sizeof(array_),4);
		 relationalArray->init(sizeof(relationalarray_),6);
		 geometryArray->set_info(array_,sizeof(array_),0);
		 relationalArray->set_info(relationalarray_,sizeof(relationalarray_),1);
		 attribute_info_geometry->ActiveAttribute(AN_Position);
		 attribute_info_geometry->ActiveAttribute(AN_Color);
		 attribute_info_geometry->ActiveAttribute(AN_UV);
		 attribute_info_geometry->ActiveAttribute(AN_NORMAL);
	}

	void Geometry::createPlane(float32 size_,glm::vec3 color){
		
			float32 array_[] = {
			-size_,	0.0,-size_,			color.x,color.y,color.z,	0.0,0.0,0.0,  0.0,1.0,0.0,
			-size_,	0.0, size_,	        color.x,color.y,color.z,	1.0,0.0,0.0,  0.0,1.0,0.0,
			 size_,	0.0,-size_,		    color.x,color.y,color.z,	0.0,1.0,0.0,  0.0,1.0,0.0,
			 size_,	0.0, size_,         color.x,color.y,color.z,    1.0,1.0,0.0,  0.0,1.0,0.0,
		};

		 unsigned int relationalarray_[] = {
			 0,1,2,3,2,1
	    };

		 geometryArray.alloc();
		 relationalArray.alloc();
		 attribute_info_geometry = 0;
		 attribute_info_geometry.alloc();
		 geometryArray->init(sizeof(array_),4);
		 relationalArray->init(sizeof(relationalarray_),6);
		 geometryArray->set_info(array_,sizeof(array_),0);
		 relationalArray->set_info(relationalarray_,sizeof(relationalarray_),1);
		 attribute_info_geometry->ActiveAttribute(AN_Position);
		 attribute_info_geometry->ActiveAttribute(AN_Color);
		 attribute_info_geometry->ActiveAttribute(AN_UV);
		 attribute_info_geometry->ActiveAttribute(AN_NORMAL);
	}


	void Geometry::createCube(float32 x_,float32 y_,float32 z_,float32 distance,glm::vec3 color)
	{
		 float32 array_[] = {
                /*********POSITION**********/					/********COLOR*********/		/**UV**/     /*NORMAL*/
		/*0*/	x_,y_,z_,										color.x,color.y,color.z,		0.0,0.0,1.0, 	 0.0,0.0,1.0,
		/*1*/	x_, y_-distance,z_,								color.x,color.y,color.z,		1.0,0.0,1.0, 	 0.0,0.0,1.0,	
		/*2*/	x_+distance,y_,z_,								color.x,color.y,color.z,		0.0,1.0,1.0, 	 0.0,0.0,1.0,
		/*3*/	x_+distance, y_-distance,z_,					color.x,color.y,color.z,		1.0,1.0,1.0, 	 0.0,0.0,1.0,
		/*4*/	x_+distance,y_,z_,								color.x,color.y,color.z,		0.0,0.0,1.0, 	 1.0,0.0,0.0,
		/*5*/	x_+distance, y_-distance,z_,					color.x,color.y,color.z,		1.0,0.0,1.0, 	 1.0,0.0,0.0,
		/*6*/	x_+distance,y_,z_-distance,						color.x,color.y,color.z,		0.0,1.0,0.0, 	 1.0,0.0,0.0,
		/*7*/	x_+distance, y_-distance,z_-distance,		    color.x,color.y,color.z,		1.0,1.0,0.0, 	 1.0,0.0,0.0,
		/*8*/	x_+distance,y_,z_-distance,						color.x,color.y,color.z,		0.0,0.0,0.0, 	 0.0,0.0,-1.0,
		/*9*/	x_+distance, y_-distance,z_-distance,			color.x,color.y,color.z,		1.0,0.0,0.0, 	 0.0,0.0,-1.0,
		/*10*/	x_,y_,z_-distance,					   		    color.x,color.y,color.z,        0.0,1.0,0.0, 	 0.0,0.0,-1.0,
		/*11*/	x_, y_-distance,z_-distance,					color.x,color.y,color.z,		1.0,1.0,0.0, 	 0.0,0.0,-1.0,
		/*12*/	x_,y_,z_-distance,						     	color.x,color.y,color.z,		0.0,0.0,0.0, 	 -1.0,0.0,0.0,
		/*13*/	x_, y_-distance,z_-distance,					color.x,color.y,color.z,		1.0,0.0,0.0, 	 -1.0,0.0,0.0,
		/*14*/	x_,y_,z_,										color.x,color.y,color.z,		0.0,1.0,1.0, 	 -1.0,0.0,0.0,
		/*15*/	x_, y_-distance,z_,								color.x,color.y,color.z,		1.0,1.0,1.0, 	 -1.0,0.0,0.0,
		/*16*/	x_, y_-distance,z_-distance,					color.x,color.y,color.z,		0.0,0.0,0.0, 	 0.0,-1.0,0.0,
		/*17*/	x_, y_-distance,z_,								color.x,color.y,color.z,		1.0,0.0,1.0, 	 0.0,-1.0,0.0,
		/*18*/	x_+distance, y_-distance,z_-distance,			color.x,color.y,color.z,		0.0,1.0,0.0, 	 0.0,-1.0,0.0,
		/*19*/	x_+distance, y_-distance,z_,					color.x,color.y,color.z,		1.0,1.0,1.0, 	 0.0,-1.0,0.0,
		/*20*/	x_,y_,z_-distance,								color.x,color.y,color.z,		0.0,0.0,0.0, 	 0.0,1.0,0.0,
		/*21*/	x_,y_,z_,										color.x,color.y,color.z,		1.0,0.0,1.0, 	 0.0,1.0,0.0,
		/*22*/	x_+distance,y_,z_-distance,						color.x,color.y,color.z,		0.0,1.0,0.0, 	 0.0,1.0,0.0,
		/*23*/	x_+distance,y_,z_,								color.x,color.y,color.z,		1.0,1.0,1.0, 	 0.0,1.0,0.0,
		};

		 unsigned int relationalarray_[] = {
			 0,1,2,3,2,1,
			 4,5,6,7,6,5,
			 8,9,10,11,10,9,
			 12,13,14,15,14,13,
			 16,17,18,19,18,17,
			 20,21,22,23,22,21

	    };

		 geometryArray.alloc();
		 relationalArray.alloc();
		 attribute_info_geometry = 0;
		 attribute_info_geometry.alloc();
		 geometryArray->init(sizeof(array_),16);
		 relationalArray->init(sizeof(relationalarray_),36);
		 geometryArray->set_info(array_,sizeof(array_),0);
		 relationalArray->set_info(relationalarray_,sizeof(relationalarray_),1);
		 attribute_info_geometry->ActiveAttribute(AN_Position);
		 attribute_info_geometry->ActiveAttribute(AN_Color);
		 attribute_info_geometry->ActiveAttribute(AN_UV);
		 attribute_info_geometry->ActiveAttribute(AN_NORMAL);
	}

	void Geometry::createCube(float size_,glm::vec3 color)
	{
		 float32 array_[] = {
                /*********POSITION**********/						/********COLOR*********/		/**UV**/     /*NORMAL*/
		/*FRONT*/
	    /*0*/	-size_, size_ , size_,										color.x,color.y,color.z,		0.0,0.0,1.0, 	 0.0,0.0,1.0,
		/*1*/	-size_,-size_ , size_,										color.x,color.y,color.z,		1.0,0.0,1.0, 	 0.0,0.0,1.0,	
		/*2*/	 size_, size_ , size_,										color.x,color.y,color.z,		0.0,1.0,1.0, 	 0.0,0.0,1.0,
		/*3*/	 size_,-size_ , size_,										color.x,color.y,color.z,		1.0,1.0,1.0, 	 0.0,0.0,1.0,
		/*RIGHT*/
		/*4*/	 size_, size_ , size_,										color.x,color.y,color.z,		0.0,0.0,1.0, 	 1.0,0.0,0.0,
		/*5*/	 size_,-size_ , size_,										color.x,color.y,color.z,		1.0,0.0,1.0, 	 1.0,0.0,0.0,
		/*6*/	 size_, size_ ,-size_,										color.x,color.y,color.z,		0.0,1.0,0.0, 	 1.0,0.0,0.0,
		/*7*/	 size_,-size_ ,-size_,										color.x,color.y,color.z,		1.0,1.0,0.0, 	 1.0,0.0,0.0,
		/*BACK*/
		/*8*/	 size_, size_ ,-size_,										color.x,color.y,color.z,		0.0,0.0,0.0, 	 0.0,0.0,-1.0,
		/*9*/	 size_,-size_ ,-size_,										color.x,color.y,color.z,		1.0,0.0,0.0, 	 0.0,0.0,-1.0,
		/*10*/	-size_, size_ ,-size_,					   					color.x,color.y,color.z,        0.0,1.0,0.0, 	 0.0,0.0,-1.0,
		/*11*/	-size_,-size_ ,-size_,										color.x,color.y,color.z,		1.0,1.0,0.0, 	 0.0,0.0,-1.0,
		/*LEFT*/
		/*12*/	-size_, size_ ,-size_,						     			color.x,color.y,color.z,		0.0,0.0,0.0, 	 -1.0,0.0,0.0,
		/*13*/	-size_,-size_ ,-size_,										color.x,color.y,color.z,		1.0,0.0,0.0, 	 -1.0,0.0,0.0,
		/*14*/	-size_, size_ , size_,										color.x,color.y,color.z,		0.0,1.0,1.0, 	 -1.0,0.0,0.0,
		/*15*/	-size_,-size_ , size_,										color.x,color.y,color.z,		1.0,1.0,1.0, 	 -1.0,0.0,0.0,
		/*BOTTOM*/
		/*16*/	-size_,-size_ ,-size_,										color.x,color.y,color.z,		0.0,0.0,0.0, 	 0.0,-1.0,0.0,
		/*17*/	-size_,-size_ , size_,										color.x,color.y,color.z,		1.0,0.0,1.0, 	 0.0,-1.0,0.0,
		/*18*/	 size_,-size_ ,-size_,										color.x,color.y,color.z,		0.0,1.0,0.0, 	 0.0,-1.0,0.0,
		/*19*/	 size_,-size_ , size_,										color.x,color.y,color.z,		1.0,1.0,1.0, 	 0.0,-1.0,0.0,
		/*TOP*/
		/*20*/	-size_, size_ ,-size_,										color.x,color.y,color.z,		0.0,0.0,0.0, 	 0.0,1.0,0.0,
		/*21*/	-size_, size_ , size_,										color.x,color.y,color.z,		1.0,0.0,1.0, 	 0.0,1.0,0.0,
		/*22*/   size_, size_ ,-size_,										color.x,color.y,color.z,		0.0,1.0,0.0, 	 0.0,1.0,0.0,
		/*23*/	 size_, size_ , size_,										color.x,color.y,color.z,		1.0,1.0,1.0, 	 0.0,1.0,0.0,
		};

		 unsigned int relationalarray_[] = {
			 0,1,2,3,2,1,
			 4,5,6,7,6,5,
			 8,9,10,11,10,9,
			 12,13,14,15,14,13,
			 16,17,18,19,18,17,
			 20,21,22,23,22,21

	    };

		 geometryArray.alloc();
		 relationalArray.alloc();
		 attribute_info_geometry = 0;
		 attribute_info_geometry.alloc();
		 geometryArray->init(sizeof(array_),16);
		 relationalArray->init(sizeof(relationalarray_),36);
		 geometryArray->set_info(array_,sizeof(array_),0);
		 relationalArray->set_info(relationalarray_,sizeof(relationalarray_),1);
		 attribute_info_geometry->ActiveAttribute(AN_Position);
		 attribute_info_geometry->ActiveAttribute(AN_Color);
		 attribute_info_geometry->ActiveAttribute(AN_UV);
		 attribute_info_geometry->ActiveAttribute(AN_NORMAL);
		
		/* float32 array_[24] = 
		{
			// Front face				
			 50.0f,  50.0f,  50.0f,		color.x,color.y,color.z,
			 50.0f, -50.0f,  50.0f,		color.x,color.y,color.z,
			-50.0f,  50.0f,  50.0f,		color.x,color.y,color.z,
			-50.0f, -50.0f,  50.0f,		color.x,color.y,color.z,
			// Back face			
			-50.0f,  50.0f, -50.0f,		color.x,color.y,color.z,
			-50.0f, -50.0f, -50.0f,		color.x,color.y,color.z,
			 50.0f,  50.0f, -50.0f, 	color.x,color.y,color.z,
			 50.0f, -50.0f, -50.0f,		color.x,color.y,color.z,
			// Left face				
			-50.0f, 50.0f, 50.0f,		color.x,color.y,color.z,
			-50.0f, -50.0f, 50.0f,		color.x,color.y,color.z,
			-50.0f, 50.0f, -50.0f,		color.x,color.y,color.z,
			-50.0f, -50.0f, -50.0f,		color.x,color.y,color.z,
			// Right face				
			50.0f, 50.0f, -50.0f,		color.x,color.y,color.z,
			50.0f, -50.0f, -50.0f,		color.x,color.y,color.z,
			50.0f, 50.0f, 50.0f, 		color.x,color.y,color.z,
			50.0f, -50.0f, 50.0f,		color.x,color.y,color.z,
			// Top face					
			-50.0f, 50.0f, -50.0f, 		color.x,color.y,color.z,
			 50.0f, 50.0f, -50.0f,		color.x,color.y,color.z,
			-50.0f, 50.0f,  50.0f, 		color.x,color.y,color.z,
			 50.0f, 50.0f,  50.0f,		color.x,color.y,color.z,
			// Bottom face
			 50.0f, -50.0f, -50.0f,		color.x,color.y,color.z,
			-50.0f, -50.0f, -50.0f,		color.x,color.y,color.z,
			 50.0f, -50.0f,  50.0f, 	color.x,color.y,color.z,
			-50.0f, -50.0f,  50.0f,		color.x,color.y,color.z,
		};
		
		glm::vec2 vSkyBoxTexCoords[4] =
		{
			glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
		};

		glm::vec3 vSkyBoxNormals[6] = 
		{
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		};*/
	}

	void Geometry::createGeometry(const char* obj,uint32 size_vertex_array,uint32 size_relation_array,void* vertexArray,void* elementarray)
	{
		
		/*if(vertexArray == 0)
		{
			if(obj != 0)
			{
				std::vector<glm::vec3> out_vertices; 
			    std::vector<glm::vec2> out_uvs;
				std::vector<glm::vec3> out_normals;
				scoped_ptr<ObjLoader> obj_;
				obj_.alloc();
				bool error;
				error=obj_->loadOBJ(obj,out_vertices,out_uvs,out_normals);
				attribute_info_geometry.alloc();
				geometryArray.alloc();
				geometryArray->init((out_vertices.size())*(sizeof(glm::vec3)));
				geometryArray->set_info(&out_vertices[0],(out_vertices.size())*(sizeof(glm::vec3)),0);
			}
			else
			{
				fprintf(stderr, "Error Obj null or vertexArray failed");
			}
		}
		else
		{
			 geometryArray.alloc();
			 relationalArray.alloc();
			 attribute_info_geometry = 0;
			 attribute_info_geometry.alloc();
			 geometryArray->init(size_vertex_array);
			 relationalArray->init(size_relation_array);
			 geometryArray->set_info(vertexArray,size_vertex_array,0);
			 relationalArray->set_info(elementarray,size_relation_array,1);
			 attribute_info_geometry->ActiveAttribute(1);
			 attribute_info_geometry->ActiveAttribute(2);
			 attribute_info_geometry->ActiveAttribute(3);
			 //AttributeMask = AttributeMask | ( 1 << 1);
		}*/
		
	}



	void Geometry::destroyGeometry()
	{


	}




}
}
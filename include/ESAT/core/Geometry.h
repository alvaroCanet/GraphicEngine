#ifndef _GEOMETRY_H__
#define _GEOMETRY_H__
#include <glm/glm.hpp>
#include <ESAT/core/Ptr/Scoped_ptr.h>
#include <ESAT/core/type_defines.h>
#include <ESAT/core/Ptr/Referenced.h>
#include <ESAT/core/Ptr/Ref_ptr.h>
#include <ESAT/core/AttributeInfo.h>

namespace ESAT {
namespace core {


class Buffer;

class Geometry : public Referenced {

private:

scoped_ptr<Buffer> geometryArray;
scoped_ptr<Buffer> relationalArray;
ref_ptr<AttributeInfo> attribute_info_geometry;

protected:
~Geometry();

public:
	
Geometry();

void createGeometry(const char* obj = 0,uint32 size_vertex_array = 0,uint32 size_relation_array = 0,void* vertexArray = 0,void* elementarray = 0);
void createCube(float32 x_,float32 y_,float32 z_,float32 distance,glm::vec3 color = glm::vec3(0.0f));
void createCube(float size_,glm::vec3 color=glm::vec3(0.0f) );
void createPlane(float32 x_, float32 y_, float32 z_, float32 width, float32 height, glm::vec3 color = glm::vec3(0.0f));
void createPlane(float32 size_,glm::vec3 color = glm::vec3(0.0f));
void destroyGeometry();

friend class Drawable;
friend class GPU;

};


}
}



#endif
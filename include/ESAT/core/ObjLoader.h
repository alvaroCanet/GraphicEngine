#ifndef OBJLOADER_H
#define OBJLOADER_H

namespace ESAT {
namespace core {

class ObjLoader {

private:
	


public:

ObjLoader();
~ObjLoader();

bool loadOBJ(const char * path,std::vector<glm::vec3> & out_vertices,
			 std::vector<glm::vec2> & out_uvs, 
			 std::vector<glm::vec3> & out_normals);


};

}
}

#endif
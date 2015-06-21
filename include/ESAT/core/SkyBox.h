#ifndef _SKYBOX_H__
#define _SKYBOX_H__
#include <string>
#include <ESAT\core\Texture.h>
#include <ESAT\core\Drawable.h>
#include <ESAT\core\Materials\MaterialSkyBox.h>

namespace ESAT{
namespace core{

class CSkybox : public Referenced
{ 
public: 

   CSkybox();
   ~CSkybox();
   void Init();
   void loadSkybox(std::string a_sDirectory, 
				   std::string a_sFront, 
				   std::string a_sBack, 
				   std::string a_sLeft, 
				   std::string a_sRight,
				   std::string a_sTop, 
				   std::string a_sBottom); 

   void renderSkybox(mat4 * view, mat4*proj); 

   void releaseSkybox(); 

private: 
  //UINT uiVAO; 
  // CVertexBufferObject vboRenderData; 
   ref_ptr<Texture> tTextures[6];
   ref_ptr<Drawable> SkyBoxDrawable;
   ref_ptr<Geometry> SkyGeo;
   ref_ptr<UniformBlock> SkyUniformBlock;
   ref_ptr<Materials::Material_SkyBox> SkyMaterial;
   
   std::string sDirectory; 
   std::string sFront, sBack, sLeft, sRight, sTop, sBottom; 
};

}
}
#endif

#include <ESAT\core\Visitor.h>
#include <ESAT\core\Drawable.h>
#include <ESAT/core/Node.h>


namespace ESAT {
namespace core {

	Visitor::Visitor()
	{
		shadowUniform.alloc();
		ref_ptr<Materials::Material_Shadow> mat_shadow;
		mat_shadow.alloc();
		mat_shadow->setData(true);
		
		shadowUniform->InitUniform(mat_shadow.get());

		shadowUniform2.alloc();
		ref_ptr<Materials::Material_Shadow> mat_shadow2;
		mat_shadow2.alloc();
		mat_shadow2->setData(false);
		
		shadowUniform2->InitUniform(mat_shadow2.get());
	
	}

	Visitor::~Visitor(){}

	void Visitor::Process(Node *node_,mat4* view,mat4 *proj,int type,vec3 eyePos,Texture* tex)
	{
		Drawable * aux;
		switch(node_->getType())
		{
			case 0 : aux = static_cast<Drawable*>(node_);
					 if(type == 1)
					 {
						 aux->DrawWithShadow(view,proj,eyePos,shadowUniform.get());
					 }
					 else if(type == 0)
					 {
						 aux->Draw(view,proj);
					 }
					 else if(type == 2)
					 {
 						 aux->DrawShadowFinal(view,proj,shadowUniform2.get(),tex);
					 }
				break;
		}
	}
}
}
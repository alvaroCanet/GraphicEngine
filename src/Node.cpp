#include <ESAT\core\Node.h>

namespace ESAT {
namespace core {


	Node::Node(TypeNode type_)
	{
		parent = 0;
		type = type_;
		scale = mat4(1.0f);
		rotation = mat4(1.0f);
		translation = mat4(1.0);
	}

	Node::~Node(){}

	void Node::addChild(Node* node_)
	{
		node_->parent = this;
		children.push_back(node_);
	}

	Node* Node::getChild(int32 num_of_child)
	{
		return children[num_of_child].get();
	}

	TypeNode Node::getType()
	{
		return type;
	}

	void Node::removeChild(Node* node_)
	{
		node_->parent = 0;
		for (int i=0; i<=children.size(); ++i)
		{
			if(node_ == children[i].get())
			{
				children.erase(children.begin()+i);
			}
		}
	}

	mat4* Node::getLocalMatrix()
	{
		return &localMatrix;
	}

	void Node::changeParent(Node* node_)
	{
		if(parent == 0)
		{
			parent = node_;
			node_->addChild(this);
		}
		else
		{
			parent->removeChild(this);
			parent = node_;
			node_->addChild(this);
		}

	}

	int32 Node::numChilds()
	{
		return children.size();
	}

	Node* Node::rootNode()
	{
		if(parent == NULL)
		{
			return this;
		}
		else
		{
			Node* node_aux;
			for(node_aux = parent;node_aux!=NULL;node_aux = node_aux->parent)
			{
				if(node_aux->parent == NULL)
				{
					return node_aux;
				}
			}
		}
		
	}

	//TRANSFORMATIONS

	void Node::Translate(vec3 value)
	{
		translation = glm::translate(value);
		CalculateLocalMatrix();
	}

	void Node::Scale(vec3 value)
	{
		scale = glm::scale(value);
		CalculateLocalMatrix();
	}

	void Node::Rotate(float value,vec3 orientation)
	{
		rotation = glm::rotate(value,orientation);
		CalculateLocalMatrix();
	}

	void Node::CalculateLocalMatrix()
	{
		localMatrix = translation * rotation * scale;
	}

	
}
}
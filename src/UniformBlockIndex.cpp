#include <ESAT\core\UniformBlockIndex.h>

namespace ESAT {
namespace core {

	UniformBlockIndex::UniformBlockIndex()
	{
		//Uniform_data.U_index.push_back(0);
	}

	UniformBlockIndex::~UniformBlockIndex(){}

	UniformBlockData* UniformBlockIndex::getUniformData()
	{
		return &Uniform_data;
	}

}
}
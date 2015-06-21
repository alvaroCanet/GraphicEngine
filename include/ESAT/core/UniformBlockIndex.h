#ifndef _UNIFORMBLOCKINDEX_H__
#define _UNIFORMBLOCKINDEX_H__


#include <vector>
#include <string>
#include <ESAT\core\type_defines.h>

namespace ESAT {
namespace core {

	struct UniformBlockData
	{
		std::vector<int32> U_offset;
		std::vector<int32> U_size;
		std::vector<std::string> U_name;
		//std::vector<char*> U_name;
		std::vector<int32> U_index;
		std::vector<int32> U_type;
		std::vector<bool> U_active;
	};

	class UniformBlockIndex
	{
	public:
		
		UniformBlockIndex();
		~UniformBlockIndex();
		UniformBlockData* getUniformData();

	private:

		UniformBlockData Uniform_data;
		friend class GPU;
		friend class UniformBlock;
	};


}
}

#endif
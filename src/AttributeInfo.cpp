#include <ESAT\core\AttributeInfo.h>
#include <stdlib.h>
#include <iostream>

namespace ESAT {
namespace core {

	AttributeInfo::AttributeInfo()
	{
		
		size_of_elements[AN_Invalid] = AT_INVALID;
		size_of_elements[AN_Position] = AT_3F;
		size_of_elements[AN_Color] = AT_3F;
		size_of_elements[AN_UV] = AT_3F;
		size_of_elements[AN_NORMAL] = AT_3F;
		memset(&index_,0,sizeof(index_));
		memset(&offset,0,sizeof(offset));
		memset(&size_,0,sizeof(size_));
		AttributeMask = 0;
		stride = 0;
		program = 0;
		attrib_num = 0;
		
	}

	void AttributeInfo::ActiveAttribute(int num)
	{
		AttributeMask = AttributeMask | ( 1 << (num - 1));
		attrib_num +=1;
		offset[num] = offset[num-1] + size_of_elements[num-1];
		size_[num-1] = size_of_elements[num];
		stride += size_[num-1]*sizeof(float);
	}

	bool AttributeInfo::IsCompatible(AttributeMaskType *atributemask_external)
	{
		if((AttributeMask & (*atributemask_external))!= AttributeMask)//Las mascaras son diferentes
		{
			fprintf(stderr,"Las mascaras no son compatibles: MaterialMask-> %d GeometryMask-> %d\n",AttributeMask,(*atributemask_external));
			return false;
		}
		fprintf(stderr,"Las mascaras son compatibles: MaterialMask-> %d GeometryMask-> %d\n",AttributeMask,(*atributemask_external));
		return true;
		
	}

	AttributeMaskType* AttributeInfo::getAttributeMask()
	{
		return &AttributeMask;
	}







}
}
#ifndef _PTR_TOOLS_H__
#define _PTR_TOOLS_H__

#include <ESAT\core\type_defines.h>

namespace ESAT {
namespace core {
namespace Tools {



	static void inicialization(char* buffer,uint32 value)
	{
		for( uint32 i = 0; i</*strlen(buffer)*/2 ; ++i) 
		{
			buffer[i] = value;
		}
	}
	

}
}
}


#endif
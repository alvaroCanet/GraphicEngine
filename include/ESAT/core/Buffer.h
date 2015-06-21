#ifndef _BUFFER_H__
#define _BUFFER_H__

#include "type_defines.h"
#include "ESAT/core/Ptr/Scoped_ptr.h"
//#include "GL/glew.h" 

namespace ESAT {
namespace core {

class data;

class Buffer 
{

private:
 
	scoped_ptr<data>datosBuffer;	

protected:

public:
 
Buffer();

~Buffer();

void init(uint32 size_,int num_elemnts);

void set_info(void *data_,uint32 size_,uint32 typeofBuffer,uint32 offset=0);

void destroy();

data * getBufferData();


};

}
}

#endif





/*template<class Type> class Buffer 
{

private:

Type * myBuffer;
unsigned int size_;


public:

Buffer()
{
	myBuffer=NULL;
}

Type *init(unsigned int size)
{
	size_ = size;
	myBuffer = new Type[sizeof(Type)*size]();
	return myBuffer;

}

void release()
{
	delete []myBuffer;
	myBuffer = NULL;
}

void setData(Type *ptr_,unsigned int size,unsigned int offset=0)
{
	if(size<=size_)
	{
		//memset(myBuffer,ptr,size*(sizeof(Type));
	}
	
}




};*/
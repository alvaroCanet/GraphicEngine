#include "ESAT\core\Buffer.h"
#include "ESAT\core\data.h"
#include "ESAT\core\GPU.h"

namespace ESAT {
namespace core {

Buffer::Buffer(){}

Buffer::~Buffer(){}

void Buffer::init(uint32 size_,int num_elemnts)
{
	datosBuffer.alloc();
	datosBuffer->num_elements_ = num_elemnts;
	datosBuffer->size_=size_;
	GPU::Instance()->InicializationBuffer(datosBuffer.get_ptr());
}

void Buffer::set_info(void *data_,uint32 size_,uint32 typeofBuffer,uint32 offset)
{
	GPU::Instance()->SetData(data_,size_,offset,datosBuffer.get_ptr(),typeofBuffer);
}

void Buffer::destroy() 
{ 
	GPU::Instance()->DestroyBuffer(datosBuffer.get_ptr());
}

data * Buffer::getBufferData(){

	return datosBuffer.get_ptr();

}


}
}
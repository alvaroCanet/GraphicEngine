#ifndef _SCOPEDARRAY_H__
#define _SCOPEDARRAY_H__

#include <cassert> //TODO: change by exceptions

namespace ESAT {
namespace core {

template<class T> class scoped_array
{

private:
	  
	T * arrayptr_;
	int size_;

public:


scoped_array(unsigned int size)
{
	arrayptr_ = NULL;
	size_ = size;
	alloc(size);
}

void release()
{
	if(arrayptr_)
	{
		//assert (size_ <= sizeof(arrayptr_) );
		delete[] arrayptr_;
		arrayptr_ = NULL;
	}
}


T* alloc(unsigned int number_) 
{
	size_ = number_;
	release();
	arrayptr_ = new T[number_];
	return arrayptr_;
}


T & operator[](int i) const 
{
    assert( arrayptr_ != 0 );
    assert( i >= 0 );
    return arrayptr_[i];
}

T* get_arrayptr(){

	return arrayptr_;
}

};

}
}
#endif
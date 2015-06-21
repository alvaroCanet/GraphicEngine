#ifndef _SCOPED_H__
#define _SCOPED_H__

namespace ESAT {
namespace core {

template<class T> class scoped_ptr
{

private:
	  
	T * ptr_;

public:

scoped_ptr()
{
	ptr_=0;
	//alloc();
}

~scoped_ptr()
{
	release();
}

void release() {

	if(ptr_!=0)
	{
		delete ptr_;
		ptr_ = 0;
	}
}


T* alloc() {
	
	release();
	ptr_ = new T();
	return ptr_;
}

T* get_ptr(){

	return ptr_;
}


T* operator->() const // never throws
{
	//assert( ptr_ != 0 );
	return ptr_;
}


};
}
}
#endif
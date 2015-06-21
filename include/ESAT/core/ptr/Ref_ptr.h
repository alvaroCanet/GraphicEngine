#ifndef _REF_PTR_H__
#define _REF_PTR_H__

#include "ESAT/core/Ptr/Referenced.h"

namespace ESAT {
namespace core {

template<class T> class ref_ptr {

private:

	T* _ptr;

public:

 T* alloc()
 {
	 release();
	 _ptr = new T();
	 if(_ptr) _ptr->ref();

	 return _ptr;
 }


 void release()
 {
	 if(_ptr) 
	 {
		 _ptr->unref();
	 }

	  _ptr = 0;
 }

 ref_ptr() { _ptr = 0; }
 
 ref_ptr(T* ptr) : _ptr(ptr) { if (_ptr) _ptr->ref();}

 ref_ptr(const ref_ptr& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->ref(); }

 ~ref_ptr() { release();  }

 void init() { _ptr = new T(); if (_ptr) _ptr->ref(); }

 ref_ptr& operator = (const ref_ptr& rp)
{
	if (_ptr==rp._ptr) return *this;
	
	T* tmp_ptr = _ptr;
	_ptr = rp._ptr;
	if (_ptr) _ptr->ref();
	// unref second to prevent any deletion of any object which might
	// be referenced by the other object. i.e rp is child of the
	// original _ptr.
	if (tmp_ptr) tmp_ptr->unref();
	return *this;
}

inline ref_ptr& operator = (T* ptr)
{
      if (_ptr==ptr) return *this;
      T* tmp_ptr = _ptr;
      _ptr = ptr;
      if (_ptr) _ptr->ref();
      // unref second to prevent any deletion of any object which might
      // be referenced by the other object. i.e rp is child of the
      // original _ptr.
      if (tmp_ptr) tmp_ptr->unref();
      return *this;
}

const T* get() const { return _ptr; }
const T& operator*() const { return *_ptr; }
const T* operator->() const { return _ptr; }

T& operator*() { return *_ptr; }
T* operator->() { return _ptr; }
T* get() { return _ptr; }


};

}
}

#endif

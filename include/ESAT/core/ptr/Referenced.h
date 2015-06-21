#ifndef _REFERENCED_H__
#define _REFERENCED_H__

#include <cassert> //TODO: change by exceptions

namespace ESAT {
namespace core {



class Referenced {

public:

void ref() 
{
 _refCount++;
}

/// do not call manually, use ref_ptr
void unref() 
{ 
    assert("Invalid unref" && (_refCount >0));

    _refCount--;
    if (_refCount == 0) delete this;
}

unsigned int getRefCounter() const
{
    return _refCount;
}


protected:

Referenced() : _refCount(0) {}
virtual ~Referenced() {}

private:

unsigned int _refCount;


};


}
}



#endif
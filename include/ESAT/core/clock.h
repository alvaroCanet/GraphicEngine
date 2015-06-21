// Copyright 2013-2014 ESAT
// all rights reserved
// author: Jose L. Hidalgo <jlhidalgo@esat.es>
//
// Clock class
//

#ifndef INCLUDE_ESAT_CLOCK_H_
#define INCLUDE_ESAT_CLOCK_H_

#include "type_defines.h"

namespace ESAT {
namespace core {

  class Clock {
  public:
    Clock();
    ~Clock();
	void reset();
	unsigned int time(unsigned int *miliseconds= 0)const;
	unsigned int seconds() const;
	unsigned long getTimer();
	//void setTimer(LARGE_INTEGER time);
	void Sleep_(unsigned int milliseconds);

  
  private:
    Clock(const Clock&);
    Clock& operator=(const Clock&);
	
	unsigned long start[2];
	unsigned long frequency[2];
  };

}  // core
}  // ESAT

#endif // INCLUDE_ESAT_CLOCK_H_

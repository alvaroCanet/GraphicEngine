// Copyright 2013-2014 ESAT
// all rights reserved
// author: Jose L. Hidalgo <jlhidalgo@esat.es>

#include <ESAT/core/clock.h>
#include <Windows.h>
#include "ESAT\core\type_defines.h"

namespace ESAT {
namespace core {

Clock::Clock() 
{
	LARGE_INTEGER t,f;
	QueryPerformanceCounter(&t);
	start[0] = t.LowPart;
	start[1] = t.HighPart;
	QueryPerformanceFrequency(&f);
	frequency[0] = f.LowPart;
	frequency[1] = f.HighPart;
}

Clock::~Clock() {}

/*void Clock::setTimer(LARGE_INTEGER time){

	start[0] = time.LowPart;
	start[1] = time.HighPart;
}*/

void Clock::reset(){
	LARGE_INTEGER t,f;
	QueryPerformanceCounter(&t);
	start[0] = t.LowPart;
	start[1] = t.HighPart;
	QueryPerformanceFrequency(&f);
	frequency[0] = f.LowPart;
	frequency[1] = f.HighPart;
	
}

unsigned int Clock::time(unsigned int *miliseconds) const {

	LARGE_INTEGER t;
	unsigned int total[2];
	QueryPerformanceCounter(&t);
	total[0] = t.HighPart - start[0];
	total[1] = t.LowPart  - start[1];
	return total[2];

}

unsigned int Clock::seconds() const{

	unsigned int micros;
	unsigned int milis = time(0);
	return milis/1000.0 + micros/1000000.0;
	
}


void Clock::Sleep_(unsigned int milliseconds)
{
	Sleep(milliseconds);
}



}  // core
}  // ESAT

//#if defined(MIMOTOR_WIN32)

// Windows 32bit -------------------------------------
#include <stdint.h>
typedef ::int8_t int8;//	char
typedef ::int16_t int16;//short
typedef ::int32_t int32;//int
typedef ::uint8_t uint8;//unsigned char
typedef ::uint16_t uint16;//unsigned short
typedef ::uint32_t uint32;//unsigned int
typedef float float32;//float
typedef void (CBFunctionMouseButton)(int32, int32);
//typedef void (GLFWmousebuttonfun)(int32, int32);
//#elif defined(MIMOTOR_PS4)

//#else
//#error Missing Platoform
//#endif
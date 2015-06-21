#ifndef _SCRIPT_H__ 
#define _SCRIPT_H__



extern "C" {
#include "../../deps/lua-5.2.2/src/lua.h"
#include "../../deps/lua-5.2.2/src/lualib.h"
#include "../../deps/lua-5.2.2/src/lauxlib.h"
}
#include "ESAT/core/type_defines.h"

namespace ESAT {
namespace core {

class Script {

private:

	 lua_State *L;


public:

	Script();
	int32 Init_(char *namefile,lua_CFunction func,char *nameLuaFunc);
	void Close();
	lua_State* get_state();
	


};

}  // core
}  // ESAT



#endif
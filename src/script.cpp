
#include <stdio.h>
#include <iostream>
#include "ESAT\core\Script.h"
/*
extern "C" {
#include "../../deps/lua-5.2.2/src/lua.h"
#include "../../deps/lua-5.2.2/src/lualib.h"
#include "../../deps/lua-5.2.2/src/lauxlib.h"
}*/
using namespace std;

namespace ESAT {
namespace core {

Script::Script(){}

int Script::Init_(char *namefile,lua_CFunction func,char *nameLuaFunc){
	
	cout << "** Init Lua" << endl;
	L = luaL_newstate();
	luaL_openlibs(L);/*Abre todas las librerias*/
	cout << "** Load chunk. without executing it" << endl;
	if (luaL_loadfile(L,namefile)) 
		{
			cout << "** Load chunck fail" << endl;
			system("pause");
			return 1;
		}
	else
		{
			cout << "** Load chunck pass" << endl;
			

			lua_pushcfunction(L,func);
			lua_setglobal(L,nameLuaFunc);

			lua_pcall(L,0,LUA_MULTRET,0);

		}
	return 0;

}

void Script::Close(){
	
	lua_close(L);

}

lua_State* Script::get_state(){

	return L;

}


}  // core
}  // ESAT











/*void report_errors(lua_State *L, int status)
{
  if ( status!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}*/
/*
int main(int argc, char** argv)
{
  for ( int n=1; n<argc; ++n ) {
    const char* file = argv[n];

    lua_State *L = lua_open();

    luaopen_io(L); // provides io.*
    luaopen_base(L);
    luaopen_table(L);
    luaopen_string(L);
    luaopen_math(L);
    luaopen_loadlib(L);

    std::cerr << "-- Loading file: " << file << std::endl;

    int s = luaL_loadfile(L, file);

    if ( s==0 ) {
      // execute Lua program
      s = lua_pcall(L, 0, LUA_MULTRET, 0);
    }

    report_errors(L, s);
    lua_close(L);
    std::cerr << std::endl;
  }

  return 0;
}*/
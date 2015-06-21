-- Copyright 2013-2014 ESAT
-- all rights reserved
-- author: Jose L. Hidalgo <jlhidalgo@esat.es>
--
-- script to generate projects

config ={
  name="GLBase",
  location="build/",
  target="build/bin/",
  glew="deps/glew-1.10.0",
  glfw="deps/glfw-3.0.3",
  glm="deps/glm-0.9.4.6",
  lua="deps/lua-5.2.2",
  AntTweakBar="deps/AntTweakBar",
}


function glfw_files(arg1,arg2)
  local list, prefix
  if arg2 == nil then
    list = arg1
    prefix = ""
  else
    prefix = arg1
    list = arg2
  end
  local result = {}
  for k,v in pairs(list) do
    table.insert(result, config.glfw.."/src/"..prefix..v)
  end
  files(result)
end

solution "ESAT"
  configurations {"Debug", "Release"}
  location(config.location)
  targetdir(config.target)
  
  language "C++"

   os.mkdir("build")
   os.mkdir("build/bin")
	--os.mkdir("")
   os.copyfile("deps/AntTweakBar/lib/AntTweakBar.dll","build/AntTweakBar.dll")
   os.copyfile("deps/AntTweakBar/lib/AntTweakBar.dll","build/bin/AntTweakBar.dll")

  includedirs {
    config.glew.."/include",
    config.glfw.."/include",
    config.glm,
    config.lua.."/src/*.*",
    config.AntTweakBar.."/include",
    "include"
  }

  libdirs {
    config.AntTweakBar.."/lib",	
  }
  
 
    
  defines {"GLEW_STATIC", "GLEW_NO_GLU"}

  configuration "Debug"
    targetsuffix "_d"
    defines {"_DEBUG"}
    flags { "Symbols" }
    
  configuration "Release"
    flags { "Optimize" }

for _,dir in ipairs(os.matchdirs("tests/*")) do
  local name = path.getbasename(dir)
  project(name)
    kind "ConsoleApp"
    files { dir.."/**.cc", dir.."/**.h" }
    links { "opengl32" }
    links { config.name.."_deps" }
    links { config.name.."_ENGINE" }
    links { "AntTweakBar" }
end


for _,dir in ipairs(os.matchdirs("testsEngine/*")) do
  local name = path.getbasename(dir)
  project(name)
    kind "ConsoleApp"
    files { dir.."/**.cc", dir.."/**.h" }
    links { "opengl32" }
    links { config.name.."_deps" }
    links { config.name.."_ENGINE" }
    links { "AntTweakBar" }
end

project(config.name.."_ENGINE")
  kind "StaticLib"
  files { "src/**.*" }
  files { "include/**.h" }

project(config.name.."_deps")
  kind "StaticLib"
  files { config.glew.."/src/glew.c" }
  files { config.lua.."/src/*.*" }
  --files { config.AntTweakBar.."/src/**.*",config.AntTweakBar.."/include/**.*" }
  glfw_files{
      "clipboard.c","context.c","gamma.c","init.c",
      "input.c","joystick.c","monitor.c","time.c","window.c", "internal.h"}
  defines {"_GLFW_USE_OPENGL" }
  configuration "windows"
    defines {"_GLFW_WIN32=1", "_GLFW_WGL=1"}
    defines {"_CRT_SECURE_NO_WARNINGS"}
    glfw_files("win32_", {
         "clipboard.c","gamma.c","init.c","joystick.c",
         "monitor.c","time.c","window.c", "platform.h"})
    glfw_files("wgl_", {"context.c"})



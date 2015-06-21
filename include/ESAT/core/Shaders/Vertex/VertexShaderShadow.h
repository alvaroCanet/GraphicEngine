static const char* vertex_shaderShadow = 
 //real time shadows
 //"attribute vec3 atrib_color;"
 "attribute vec3 atrib_position;" 
 //"attribute vec2 atrib_uv;"

 //"uniform vec3 eye_Pos;"
 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"
 //"uniform vec3 u_color;"
 
 //"varying vec3 var_color;"
 "varying vec4 var_pos;"
 //"varying vec3 eye_pos;"
 //"varying vec2 var_uv;"

"void main()"                                                                   
"{"                                                                          
    "gl_Position =  u_projection * u_view * u_model  * vec4(atrib_position,1.0);"
	"var_pos = u_projection * u_view * u_model  * vec4(atrib_position,1.0);"
	//"var_pos = u_view * u_model  * vec4(atrib_position,1.0);"
	//"var_uv = atrib_uv;"

"}";


static const char *vertex_shadow =

 "attribute vec3 atrib_position;" 
 
 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"

 "uniform mat4 ModelLight;"
 "uniform mat4 ViewLight;"
 "uniform mat4 ProjLight;"
 
 //"uniform vec3 u_color;"

 //"varying vec3 var_color;"
 "varying vec4 posLightSpace;"
 
 "varying vec2 v_uv;"
 "varying vec4 v_ShadowCoord;"

 "void main()"                                                                   
"{"
	"gl_Position =  u_projection * u_view * u_model  * vec4(atrib_position,1.0);"
	"posLightSpace = (ProjLight * ViewLight * u_model) * vec4(atrib_position,1.0) ;"
	//"posLightSpace = ProjLight * ViewLight * u_model * vec4(atrib_position,1.0) ;"
"};";




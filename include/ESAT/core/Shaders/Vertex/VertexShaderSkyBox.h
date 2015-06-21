static const char* vertex_shader = 
 //"attribute vec3 atrib_color;"
 "attribute vec3 atrib_position;" 
 "attribute vec3 atrib_uv;"
 "attribute vec3 atrib_normal;"

 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"
 "uniform vec3 u_color;"

 "varying vec3 TexCoord0;" 

"void main()"                                                                   
"{"                                                                          
    //"gl_Position =  u_projection * u_view * u_model  * vec4(0.5*atrib_position,1.0);"//vec4(0.5 * atrib_position.x, 0.5 * atrib_position.y, atrib_position.z, 1.0);"
	//"TexCoord0= atrib_uv;"
	//"vec3 normal = (u_view*u_model*vec4(0.5*atrib_position,0)).xyz;"
	//"TexCoord0 = normal * gl_Normal;"
	//"TexCoord0.z =  atrib_normal;"
	//"TexCoord0.z =  1.0;"
	"vec4 MVPPos = u_projection * u_view * u_model  * vec4(0.5*atrib_position,1.0);"
	"TexCoord0   = 0.5*atrib_position; "
	"gl_Position = MVPPos;"
	
"}";


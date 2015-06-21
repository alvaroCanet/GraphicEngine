static const char* vertex_shader = 
 //"attribute vec3 atrib_color;"
 "attribute vec3 atrib_position;" 
 "attribute vec2 atrib_uv;"

 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"
 "uniform vec3 u_color;"
 
 "varying vec2 TexCoord0;"
 "varying vec3 var_color;"

"void main()"                                                                   
"{"                                                                          
    "gl_Position =  u_projection * u_view * u_model  * vec4(0.5*atrib_position,1.0);"//vec4(0.5 * atrib_position.x, 0.5 * atrib_position.y, atrib_position.z, 1.0);"
	 "TexCoord0 = atrib_uv;"
	 "var_color = u_color;"  
"}";





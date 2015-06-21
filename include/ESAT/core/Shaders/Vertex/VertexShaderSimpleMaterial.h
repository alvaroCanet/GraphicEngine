static const char* vertex_shaderSimpleMaterial = 
 //"attribute vec3 atrib_color;"
 "attribute vec3 atrib_position;" 
 //"attribute vec2 atrib_uv;"

 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"
 "uniform vec3 u_color;"
 
 "varying vec3 var_color;"

"void main()"                                                                   
"{"                                                                          
    "gl_Position =  u_projection * u_view * u_model  * vec4(0.5*atrib_position,1.0);"
	"var_color = u_color;"  
"}";




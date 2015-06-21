static const char* vertex_shaderAmbient = 
 
"attribute vec3 atrib_position;" 

 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"
 "uniform vec3 u_color;"

 "varying vec3 var_color;"

"void main()"                                                                   
"{"   
	"var_color = u_color;"                                                                         
    "gl_Position =  u_projection * u_view * u_model  * vec4(0.5*atrib_position,1.0);"
"}";
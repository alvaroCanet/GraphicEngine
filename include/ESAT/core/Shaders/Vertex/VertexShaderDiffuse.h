static const char* vertex_shaderDiffuse = 


 "attribute vec3 atrib_position;"
 "attribute vec3 atrib_normal;"

 "uniform mat4 u_view;"
 "uniform mat4 u_projection;"
 "uniform mat4 u_model;"
 "uniform vec3 u_color;"

 "varying vec3 var_color;"
 "varying vec3 var_Normal;"
 "varying vec3 var_pos;"

"void main()"                                                                   
"{"   
	"var_color = u_color;"
	"var_Normal = (u_model * vec4(atrib_normal, 0.0)).xyz;"
	"var_pos = (u_model * vec4(atrib_position, 1.0)).xyz;"
    "gl_Position =  u_projection * u_view * u_model  * vec4(0.5*atrib_position,1.0);"
"}";
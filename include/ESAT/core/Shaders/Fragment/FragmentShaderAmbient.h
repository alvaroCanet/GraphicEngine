static const char* fragment_shaderAmbient = 
 
"varying vec3 var_color;"
"uniform float u_ambientIntensity;"
"uniform vec3 u_lighColor;"
                                                                              
"void main()"                                                                   
"{"                                                                             
   " gl_FragColor =  vec4(var_color,1.0) * vec4(u_lighColor,1.0)* u_ambientIntensity;"//vec4(u_lighColor,1.0);"// * u_ambientIntensity ; "//vec4(var_color,1.0);"                             
"}";
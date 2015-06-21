static const char* fragment_shader = 

"uniform sampler2D gSampler;"

"varying vec2 TexCoord0;"
"varying vec3 var_color;"
                                                                              
"void main()"                                                                   
"{"                                                                             
" gl_FragColor = texture2D(gSampler, TexCoord0.st) + vec4(var_color,1.0);"                         
"}";


static const char* fragment_shader = 
"varying vec3 TexCoord0;" 
"uniform samplerCube gCubemapTexture;"                                                
                                                                                    
"void main()"                                                                         
"{"
"vec3 norm = normalize(TexCoord0);"
//"vec3 norm = TexCoord0;"
//"vec3 aux = vec3(1.0,1.0,1.0);"
"vec4 frag = texture(gCubemapTexture, norm);"
//"gl_FragColor = vec4(1,1,TexCoord0.z,1);"
//"gl_FragColor  = vec4(norm,1.0); "//vec4(norm,1.0); ;" frag;
"gl_FragColor = frag;"

"}";


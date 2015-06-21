static const char* fragment_shaderDiffuse = 
 
"varying vec3 var_Normal;"
"varying vec3 var_color;"
"varying vec3 var_pos;"

"uniform float u_ambientIntensity;"
"uniform vec3 u_lighColor;"
"uniform vec3 u_lightPosition;"
"uniform float u_IntensityDiffuse;"
                                                                              
"void main()"                                                                   
"{" 
	" vec4 lightAmbient = vec4(u_lighColor,1.0)* u_ambientIntensity;"
	" vec3 u_lightDirection = var_pos - u_lightPosition;"
	" vec3 light_direction_normalize = normalize(u_lightDirection);"
	" float DiffuseFactor = max(dot(normalize(var_Normal), - light_direction_normalize),0.0);"
	" vec4 lightDiffuse;"
	" if (DiffuseFactor > 0)" 
	" {"
		"float DiffuseIntensity = u_IntensityDiffuse;"
		"lightDiffuse =  vec4(u_lighColor,1.0) * DiffuseFactor * DiffuseIntensity;" 
	" }"
	" else" 
	" {"
		//"lightDiffuse = vec4(0, 0, 0, 0);"
	" }"

   " gl_FragColor = vec4(var_color,1.0) * ( lightAmbient + lightDiffuse) ;"//vec4(u_lighColor,1.0);"// * u_ambientIntensity ; "//vec4(var_color,1.0);"                             
   //"  gl_FragColor = vec4(light_direction_normalize,1.0);"
   "}";
static const char* fragment_shaderSpecular = 
 
"varying vec3 var_Normal;"
"varying vec3 var_color;"
"varying vec3 var_pos;"

"uniform float u_ambientIntensity;"
"uniform vec3 u_lighColor;"
"uniform vec3 u_lightPosition;"
"uniform vec3 u_eyePosition;"
"uniform float u_IntensityDiffuse;"
"uniform float u_brightnessIntensity;"
"uniform float u_specularIntensity;"
                                                                              
"void main()"                                                                   
"{" 
	/*AMBIENT*/
	" vec4 lightAmbient = vec4(u_lighColor,1.0)* u_ambientIntensity;"
	/*DIFUSE*/
	" vec3 lightDirection = var_pos - u_lightPosition;"
	" vec3 light_direction_normalize = normalize(lightDirection);"
	" float DiffuseFactor = max(dot(normalize(var_Normal), - light_direction_normalize),0.0);"
	" vec4 lightDiffuse =  vec4(u_lighColor,1.0) * DiffuseFactor * u_IntensityDiffuse;"

	/*SPECULAR*/
	"vec3 vertexToEye = normalize(u_eyePosition - var_pos);"
	"vec3 lightReflect = lightDirection  + (2*(normalize(var_Normal))*((normalize(-var_Normal))*lightDirection));"
	//"vec3 lightReflect = reflect(lightDirection,normalize(var_Normal));"
	"vec3 lightReflectNormalize = normalize(lightReflect);"
	"float SpecularFactor = dot(vertexToEye,lightReflectNormalize);"
	"SpecularFactor = max(pow(SpecularFactor,u_brightnessIntensity),0.0);"
	"vec4 lightSpecular = vec4(u_lighColor,1.0) * u_specularIntensity * SpecularFactor;"
   
	/*"vec4 SpecularColor = vec4(0, 0, 0, 0);"                    
    "vec3 lightReflect = reflect(lightDirection,normalize(var_Normal));"
    "float SpecularFactor = dot(vertexToEye, lightReflect);"                      
    "SpecularFactor = pow(SpecularFactor, u_brightnessIntensity);"                       
    "if (SpecularFactor > 0) {"                                                   
    "SpecularColor = vec4(u_lighColor, 1.0f) *"                   
    "u_brightnessIntensity * SpecularFactor;"                 
    "}"      */                             

	" gl_FragColor = vec4(var_color,1.0) * ( lightAmbient + lightDiffuse + lightSpecular);"//SpecularFactor) ;"//vec4(u_lighColor,1.0);"// * u_ambientIntensity ; "//vec4(var_color,1.0);"                             
   //"  gl_FragColor = vec4(light_direction_normalize,1.0);"
   "}";
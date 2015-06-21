static const char* fragment_shaderShadow = 

"varying vec3 var_color;"
"varying vec4 var_pos;"
"varying vec3 eye_pos;"
"varying vec2 var_uv;"

"uniform sampler2D shadow;"

"const float Near = 0.1;"
"const float Far = 25.0;"
"const float LinearDepthConstant = 1.0 / (Far - Near);"
/*
"vec4 pack (float depth)"
"{"
"   const vec4 bias = vec4(1.0 / 255.0,"
"          1.0 / 255.0,"
"          1.0 / 255.0,"
"          0.0);"

"   float r = depth;"
"   float g = fract(r * 255.0);"
"   float b = fract(g * 255.0);"
"   float a = fract(b * 255.0);"
"   vec4 colour = vec4(r, g, b, a);"
    
"   return colour - (colour.yzww * bias);"
"}"
*/

"void main() {"
    "   vec3 aux_ = gl_FragCoord.xyz /gl_FragCoord.w;"					
	"   float Depth = aux_.z;"
    "   float linearDepth= Depth * LinearDepthConstant;"
	"   aux_.z = linearDepth;"

	//"float Depth = texture(shadow, var_uv).x;"
	//"Depth = 1.0 - (1.0 - gl_FragCoord.z) * 25.0;"
	"gl_FragColor = vec4(aux_,1.0);"
"}";

/*
"void main()"                                                                   
"{"  
"const float Near = 0.01;"
"const float Far = 25.0;"
"const float LinearDepthConstant = 1.0 / (Far - Near);"

"float Depth = gl_FragCoord.z / gl_FragCoord.w;"
"Depth = Depth * LinearDepthConstant;"

" gl_FragColor = Depth;"     

"}";*/

static const char *fragment_shadow =
"uniform vec3 u_color;"
"uniform sampler2D gShadowMap;"


"varying vec4 posLightSpace;"

"const float Near = 0.1;"
"const float Far = 25.0;"
"const float LinearDepthConstant = 1.0 / (Far - Near);"

"void main()"                                                                   
"{"
"	vec3 color_ = vec3(1.0,0.0,0.0); "
//"	gl_FragColor = vec4(color_ * CalcShadowFactor(posLightSpace),1.0);"
"    vec3 ProjCoords = posLightSpace.xyz / posLightSpace.w;		   "
"    vec2 UVCoords;												   "
"    UVCoords.x = 0.5 * ProjCoords.x + 0.5;						   "
"    UVCoords.y = 0.5 * ProjCoords.y + 0.5;						   "
"    float z = 0.5 * posLightSpace.z + 0.5;						   "
"    float z2 = posLightSpace.z * LinearDepthConstant;						   "
"    float Depth = texture(gShadowMap, UVCoords).z;"
"    if (Depth < (z2 +0.0001 ))									   "
"     {   gl_FragColor = vec4(color_,1.0)*0.5;}				    "
"    else														   "
"    {    gl_FragColor = vec4(color_,1.0)*1.0;}				   "



//" gl_FragColor =z2;"//z/10;"
//"gl_FragColor = UVCoords.x;"//vec4(vec3(UVCoords.xy,z),1.0);"
//"gl_FragColor = vec4(UVCoords,1,1);"
//"gl_FragColor = texture(gShadowMap, UVCoords.xy).z;"// vec4(UVCoords,1,1);"
//" gl_FragColor = z;"
//"   gl_FragColor = CalcShadowFactor(posLightSpace);"

"}";



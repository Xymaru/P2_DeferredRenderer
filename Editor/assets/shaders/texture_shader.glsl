#if defined(VERTEX_SHADER)

layout(location = 0) in vec3 a_Pos;
//layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 a_TexCoord;
//layout(location = 3) in vec3 aTangent;
//layout(location = 4) in vec3 aBitangent;

out vec2 v_TexCoord;

void main(){
	v_TexCoord = a_TexCoord;
	
	float cscale = 5.0;
	
	gl_Position = vec4(a_Pos, cscale);
	
	gl_Position.z = -gl_Position.z;
}

#elif defined(FRAGMENT_SHADER)

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main(){
	o_Color = texture(u_Texture, v_TexCoord);
}

#endif
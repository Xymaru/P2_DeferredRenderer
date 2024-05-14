#if defined(VERTEX_SHADER)

layout(location = 0) in vec3 a_Pos;
//layout(location = 1) in vec3 a_Normals;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main(){
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);
}

#elif defined(FRAGMENT_SHADER)
	layout(location = 0) out vec4 o_Color;

	void main(){
		o_Color = vec4(1.0);
	}
#endif
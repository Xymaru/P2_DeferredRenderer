#if defined(VERTEX_SHADER)

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normals;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec3 v_Normals;
out vec3 v_Position;

void main(){
	v_Normals = transpose(inverse(mat3(u_Model))) * a_Normals;
	//v_Normals = vec3(u_Model * vec4(a_Normals, 1.0));
	v_Position = (u_Model * vec4(a_Pos, 1.0)).xyz;

	gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);
}

#elif defined(FRAGMENT_SHADER)
layout(location = 0) out vec4 o_Color;
layout(location = 1) out vec4 o_Normals;
layout(location = 2) out vec4 o_Position;
layout(location = 3) out vec4 o_Depth;

in vec3 v_Normals;
in vec3 v_Position;

vec4 get_linear_depth(){
	float near = 0.1;
	float far = 100.0;

	float z = gl_FragCoord.z * 2.0 - 1.0;

	float d = (2.0 * near * far) / (far + near - z * (far - near));

	float depth = d / far;

	return vec4(vec3(depth), 1.0);
}

void main(){
	o_Color = vec4(1.0);
	o_Normals = vec4(normalize(v_Normals), 1.0);
	o_Position = vec4(v_Position, 1.0);
	o_Depth = get_linear_depth();
}
#endif
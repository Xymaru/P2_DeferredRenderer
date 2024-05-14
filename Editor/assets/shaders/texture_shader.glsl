struct PointLight
{
	vec3 color;
	vec3 position;
};

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
	vec3 position;
};

#if defined(VERTEX_SHADER)

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec2 a_TexCoord;
//layout(location = 3) in vec3 aTangent;
//layout(location = 4) in vec3 aBitangent;

out vec2 v_TexCoord;
out vec3 v_Position;
out vec3 v_Normals;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main(){
	v_TexCoord = a_TexCoord;
	v_Position = (u_Model * vec4(a_Pos, 1.0)).xyz;
	//v_Normals = vec3(u_Model * vec4(a_Normals, 0.0));
	v_Normals = transpose(inverse(mat3(u_Model))) * a_Normals;


	gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);
}

#elif defined(FRAGMENT_SHADER)

layout(location = 0) out vec4 o_Color;
layout(location = 1) out vec4 o_Normals;
layout(location = 2) out vec4 o_Position;
layout(location = 3) out vec4 o_Depth;

in vec2 v_TexCoord;
in vec3 v_Position;
in vec3 v_Normals;

uniform vec3 u_CameraPos;

uniform unsigned int u_PointLightCount;
uniform PointLight u_PointLights[16];

uniform unsigned int u_DirectionalLightCount;
uniform DirectionalLight u_DirectionalLights[16];

uniform sampler2D u_Texture;

vec3 calc_point_light(in PointLight light){
	float ambient = 0.1;
	vec3 norm = normalize(v_Normals);

	vec3 light_dir = normalize(u_PointLights[0].position - v_Position);

	float diffuse = max(dot(norm, light_dir), 0.0);

	return (ambient + diffuse) * light.color;
}

vec4 get_linear_depth(){
	float near = 0.1;
	float far = 100.0;

	float z = gl_FragCoord.z * 2.0 - 1.0;

	float d = (2.0 * near * far) / (far + near - z * (far - near));

	float depth = d / far;

	return vec4(vec3(depth), 1.0);
}

void main(){
	vec3 total_light = vec3(0.0);

	for(int i=0;i<u_PointLightCount;i++){
		total_light += calc_point_light(u_PointLights[i]);
	}

	total_light = min(total_light, vec3(1.0));

	vec4 light_result = vec4(total_light, 1.0);

	vec4 obj_color = texture(u_Texture, v_TexCoord).rgbr;
	
	o_Color = obj_color;// * light_result;
	o_Normals = vec4(normalize(v_Normals), 1.0);
	o_Position = vec4(v_Position, 1.0);
	o_Depth = get_linear_depth();
}

#endif
struct PointLight
{
	vec3 color;
	vec3 position;
};

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
};

#if defined(VERTEX_SHADER)
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main(){
	v_TexCoord = a_TexCoord;

	gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0);
}
#elif defined(FRAGMENT_SHADER)

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform unsigned int u_PointLightCount;
uniform PointLight u_PointLights[16];

uniform unsigned int u_DirectionalLightCount;
uniform DirectionalLight u_DirectionalLights[16];

uniform vec3 u_CameraPos;

uniform sampler2D u_Albedo;
uniform sampler2D u_Normals;
uniform sampler2D u_Positions;

vec3 calc_point_light(in PointLight light, in vec4 color, in vec3 normals, in vec3 position, in vec3 view_dir) {
    float linear = 0.7;
    float quadratic = 1.8;
    float light_max = max(max(light.color.r, light.color.g), light.color.b);
    float radius = (-linear + sqrt(linear * linear - 4.0 * quadratic * (1.0 - (256.0 / 5.0) * light_max))) / (2.0 * quadratic);

    float d = length(light.position - position);

    if (d > radius) return vec3(0.0);

    vec3 norm = normalize(normals);

    float intensity = 1.0;

    // Ambient
    float ambient = 0.1;
    vec3 ambient_color = ambient * color.rgb * light.color;

    // Diffuse
    vec3 light_dir = normalize(light.position - position);
    float diffuse = max(dot(norm, light_dir), 0.0);
    vec3 diffuse_color = diffuse * color.rgb * light.color;

    // Specular
    float spec_power = 32.0;
    vec3 hwd = normalize(light_dir + view_dir);
    float specular = pow(max(dot(norm, hwd), 0.0), spec_power);
    vec3 specular_color = specular * color.a * light.color;

    return (ambient_color + diffuse_color + specular_color) * intensity;
}

vec3 calc_directional_light(in DirectionalLight light, in vec4 color, in vec3 normals, in vec3 view_dir) {
    vec3 norm = normalize(normals);

    vec3 light_dir = normalize(light.direction);

    float intensity = 0.1;

    // Ambient
    float ambient = 0.1;
    vec3 ambient_color = ambient * color.rgb * light.color;

    // Diffuse
    float diffuse = max(dot(norm, light_dir), 0.0);
    vec3 diffuse_color = diffuse * color.rgb * light.color;

    return (ambient_color + diffuse_color) * intensity;
}

void main() {
    vec2 flipped_uv = v_TexCoord;
    flipped_uv.y = 1.0 - flipped_uv.y;

    vec4 obj_color = texture(u_Albedo, flipped_uv);
    vec3 obj_normals = normalize(texture(u_Normals, flipped_uv).rgb);
    vec3 obj_pos = texture(u_Positions, flipped_uv).rgb;

    vec3 view_dir = normalize(u_CameraPos - obj_pos);

    // Base ambient color
    vec3 total_light = obj_color.rgb * 0.1;

    // Point lights
    for (int i = 0; i < u_PointLightCount; i++) {
        total_light += calc_point_light(u_PointLights[i], obj_color, obj_normals, obj_pos, view_dir);
    }

    // Directional lights
    for (int i = 0; i < u_DirectionalLightCount; i++) {
        total_light += calc_directional_light(u_DirectionalLights[i], obj_color, obj_normals, view_dir);
    }

    vec3 final_color = total_light;

    o_Color = vec4(final_color, 1.0);
}

#endif
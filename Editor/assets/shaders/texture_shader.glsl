#if defined(VERTEX_SHADER)

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_Position;
out vec3 v_Normals;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
    v_TexCoord = a_TexCoord;
    vec4 world_pos = u_Model * vec4(a_Pos, 1.0);
    v_Position = world_pos.xyz;
    mat3 normal_matrix = transpose(inverse(mat3(u_Model)));
    v_Normals = normalize(normal_matrix * a_Normals);

    gl_Position = u_Projection * u_View * world_pos;
}

#elif defined(FRAGMENT_SHADER)

layout(location = 0) out vec4 o_Color;
layout(location = 1) out vec4 o_Normals;
layout(location = 2) out vec4 o_Position;
layout(location = 3) out vec4 o_Depth;

in vec2 v_TexCoord;
in vec3 v_Position;
in vec3 v_Normals;

uniform sampler2D u_Texture;

float get_linear_depth() {
    float near = 0.1;
    float far = 100.0;
    float depth = gl_FragCoord.z;
    return (2.0 * near) / (far + near - depth * (far - near));
}

void main() {
    vec4 obj_color = texture(u_Texture, v_TexCoord).rgba;

    o_Color = obj_color;
    o_Normals = vec4(normalize(v_Normals), 1.0);
    o_Position = vec4(v_Position, 1.0);
    o_Depth = vec4(vec3(get_linear_depth()), 1.0);
}

#endif
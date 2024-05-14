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

	uniform sampler2D u_Texture;

	void main(){
		vec2 flipped_uv = v_TexCoord;
		flipped_uv.y = 1.0 - flipped_uv.y;
		
		o_Color = texture(u_Texture, flipped_uv);
	}
#endif
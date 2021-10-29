// FRAGMENT SHADER
#version 430 core

in vec2 v_out_textureCoordinate;
in vec3 v_out_color;

out vec4 f_out_color;

uniform vec4 f_uni_color;
uniform sampler2D f_uni_texture;

void main()
{
	f_out_color = vec4(v_out_color, 1.0);
}
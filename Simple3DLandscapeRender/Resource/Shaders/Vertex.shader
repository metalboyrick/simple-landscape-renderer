// VERTEX SHADER
#version 430 core

// location means the index of the attribute
layout(location = 0) in vec3 v_in_position;
layout(location = 1) in vec3 v_in_color;
layout(location = 2) in vec2 v_in_textureCoordinate;

out vec2 v_out_textureCoordinate;
out vec3 v_out_color;

uniform mat4 v_uni_model;
uniform mat4 v_uni_view;
uniform mat4 v_uni_projection;

void main()
{
	gl_Position = v_uni_projection * v_uni_view * v_uni_model * vec4(v_in_position, 1.0);
	v_out_textureCoordinate = v_in_textureCoordinate;
	v_out_color = v_in_color;
}
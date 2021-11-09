// VERTEX SHADER
#version 430 core

// location means the index of the attribute
layout(location = 0) in vec3 v_in_position;
layout(location = 1) in vec3 v_in_color;
layout(location = 2) in vec2 v_in_textureCoordinate;
layout(location = 3) in vec3 v_in_normal;

out vec2 v_out_textureCoordinate;
out vec3 v_out_color;
out vec3 v_out_surfaceNormal;
out vec3 v_out_toLightVector;
out vec3 v_out_toCameraVector;
out vec3 v_out_toViewVector;

uniform mat4 v_uni_model;
uniform mat4 v_uni_view;
uniform mat4 v_uni_projection;
uniform vec3 v_uni_lightPosition;
uniform mat4 v_uni_viewMatrix;

void main()
{
	// general object position in world coordinates
	vec4 worldPosition = v_uni_model * vec4(v_in_position, 1.0);

	gl_Position = v_uni_projection * v_uni_view * worldPosition;
	v_out_textureCoordinate = v_in_textureCoordinate;
	v_out_color = v_in_color;

	// compute net surface normal
	v_out_surfaceNormal = (v_uni_model * vec4(v_in_normal, 1.0)).xyz;
	v_out_toLightVector = v_uni_lightPosition - worldPosition.xyz;
	v_out_toViewVector = (inverse(v_uni_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}
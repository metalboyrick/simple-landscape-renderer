// FRAGMENT SHADER
#version 430 core

in vec3 v_out_surfaceNormal;
in vec3 v_out_position;
in vec3 v_out_toViewVector;

out vec4 f_out_color;

uniform samplerCube f_uni_texture;
uniform vec3 f_uni_cameraPos;

void main()
{
	vec3 unitToViewVector = normalize(v_out_toViewVector);
	vec3 unitSurfaceNormal = normalize(v_out_surfaceNormal);

	vec3 reflectedView = refract(-1 * unitToViewVector, unitSurfaceNormal, 1.00 /1.52);

	f_out_color = vec4(texture(f_uni_texture, reflectedView).rgb, 1.0);

}
// FRAGMENT SHADER
#version 430 core

in vec3 v_out_surfaceNormal;
in vec3 v_out_position;
in vec3 v_out_toViewVector;

out vec4 f_out_color;

uniform samplerCube f_uni_texture;

void main()
{
	vec3 unitToViewVector = normalize(v_out_toViewVector);
	vec3 unitSurfaceNormal = normalize(v_out_surfaceNormal);

	vec3 reflectedView = reflect(-1 * unitToViewVector, unitSurfaceNormal);

	f_out_color = vec4(texture(f_uni_texture, reflectedView).rgb, 1.0f) + vec4(0.2, 0,0,0);

}
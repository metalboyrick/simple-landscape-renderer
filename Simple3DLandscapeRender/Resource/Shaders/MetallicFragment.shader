// FRAGMENT SHADER
#version 430 core

in vec3 v_out_surfaceNormal;
in vec3 v_out_position;
in vec3 v_out_toViewVector;
in vec3 v_out_toLightVector;

out vec4 f_out_color;

uniform samplerCube f_uni_texture;
uniform vec3 f_uni_lightColor;
uniform vec3 f_uni_ambient;

void main()
{
	vec3 unitToViewVector = normalize(v_out_toViewVector);
	vec3 unitSurfaceNormal = normalize(v_out_surfaceNormal);
	vec3 unitToLightVector = normalize(v_out_toLightVector);

	vec3 reflectedView = reflect(-1 * unitToViewVector, unitSurfaceNormal);

	float dotProd = dot(unitSurfaceNormal, unitToLightVector);

	// prevent values lower than 0
	float brightness = max(dotProd, 0);

	vec3 diffuseColor = brightness * f_uni_lightColor;
	f_out_color = vec4(diffuseColor + f_uni_ambient, 1.0) * vec4(texture(f_uni_texture, reflectedView).rgb, 0.74);

}
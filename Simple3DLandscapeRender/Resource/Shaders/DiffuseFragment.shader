// FRAGMENT SHADER
#version 430 core

in vec2 v_out_textureCoordinate;
in vec3 v_out_color;
in vec3 v_out_surfaceNormal;
in vec3 v_out_toLightVector;

out vec4 f_out_color;

uniform vec4 f_uni_color;
uniform vec3 f_uni_lightColor;
uniform sampler2D f_uni_texture;

void main()
{
	vec3 unitSurfaceNormal = normalize(v_out_surfaceNormal);
	vec3 unitToLightVector = normalize(v_out_toLightVector);

	float dotProd = dot(unitSurfaceNormal, unitToLightVector);
	
	// prevent values lower than 0
	float brightness = max(dotProd, 0);

	vec3 diffuseColor = brightness * f_uni_lightColor;

	f_out_color = vec4(diffuseColor, 1.0) * vec4(v_out_color, 1.0);
}
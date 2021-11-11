// FRAGMENT SHADER
#version 430 core

in vec2 v_out_textureCoordinate;
in vec3 v_out_color;
in vec3 v_out_surfaceNormal;
in vec3 v_out_toLightVector;
in vec3 v_out_toViewVector;

out vec4 f_out_color;

uniform vec4 f_uni_color;
uniform vec3 f_uni_lightColor;
uniform int f_uni_shineDamper;
uniform sampler2D f_uni_texture;
uniform float f_uni_ambient;

void main()
{
	// diffuse
	vec3 unitSurfaceNormal = normalize(v_out_surfaceNormal);
	vec3 unitToLightVector = normalize(v_out_toLightVector);
	float dotProd = dot(unitSurfaceNormal, unitToLightVector);

	// prevent values lower than 0
	float brightness = max(dotProd, 0);
	vec3 diffuseColor = brightness * f_uni_lightColor;

	// specular (blinnphong)
	vec3 unitFromLightVector = -1 * unitToLightVector;
	vec3 unitToViewVector = normalize(v_out_toViewVector);
	vec3 reflectedNormal = reflect(unitFromLightVector, unitSurfaceNormal);

	// blinnphong
	vec3 halfwayVector = normalize(-1 * unitFromLightVector + unitToViewVector);

	float specularFactor = dot(unitSurfaceNormal, halfwayVector);
	specularFactor = max(specularFactor, 0.0);
	vec3 specularColor =  pow(specularFactor, f_uni_shineDamper) * f_uni_lightColor;

	//combine
	f_out_color = ((vec4(diffuseColor, 1.0) + f_uni_ambient) * vec4(v_out_color, 1.0)) + vec4(specularColor, 1.0);
}
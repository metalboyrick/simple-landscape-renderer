#include "Light.h"

Light::Light(float p_x, float p_y, float p_z, float p_r, float p_g, float p_b)
{
	position[0] = p_x;
	position[1] = p_y;
	position[2] = p_z;

	color[0] = p_r;
	color[1] = p_g;
	color[2] = p_b;
}

Light::~Light()
{
}

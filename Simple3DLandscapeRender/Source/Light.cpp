#include "Light.h"

Light::Light(float p_x, float p_y, float p_z, float p_r, float p_g, float p_b)
{
	m_position[0] = p_x;
	m_position[1] = p_y;
	m_position[2] = p_z;

	m_color[0] = p_r;
	m_color[1] = p_g;
	m_color[2] = p_b;
}

Light::~Light()
{
}

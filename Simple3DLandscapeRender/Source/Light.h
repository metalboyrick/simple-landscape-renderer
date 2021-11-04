#pragma once

#include <glm/glm.hpp>

class Light
{
private: 
	glm::vec3 m_position;
	glm::vec3 m_color;

public:
	Light(float p_x, float p_y, float p_z, float p_r, float p_g, float p_b);
	~Light();

	inline glm::vec3 getPosition() const { return m_position; };
	inline glm::vec3 getColor() const { return m_color; };
};


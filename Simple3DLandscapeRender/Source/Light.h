#pragma once

#include <glm/glm.hpp>

class Light
{
private: 
	

public:
	Light(float p_x, float p_y, float p_z, float p_r, float p_g, float p_b);
	~Light();

	glm::vec3 position;
	glm::vec3 color;
};


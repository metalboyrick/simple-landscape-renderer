#pragma once

#include "ShaderProgram.h"
#include "Model.h"
#include "Skybox.h"

#include <glm/glm.hpp>


class Renderer
{
public:
	Renderer();
	~Renderer();

	void prepare() const;
	void drawModel(Model& p_Model, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const;
	void drawRotatingModel(Model& p_Model, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const;
	void drawSkybox(Skybox& p_skybox, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const;
	
};


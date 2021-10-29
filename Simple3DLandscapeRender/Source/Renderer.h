#pragma once

#include "ShaderProgram.h"
#include "RawModel.h"
#include "Skybox.h"

#include <glm/glm.hpp>


class Renderer
{
public:
	Renderer();
	~Renderer();

	void prepare() const;
	void drawRawModel(RawModel& p_rawModel, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const;
	void drawRotatingRawModel(RawModel& p_rawModel, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const;
	void drawSkybox(Skybox& p_skybox, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const;
	
};


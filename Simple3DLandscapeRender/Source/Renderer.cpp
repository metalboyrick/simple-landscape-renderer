#include "Renderer.h"
#include "Common.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <GLFW/glfw3.h>

Renderer::Renderer()
{
	// enable depth test
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
}

void Renderer::prepare() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawModel(Model& p_Model, glm::mat4 p_viewMatrix, ShaderProgram& p_shader, Light& p_light) const
{
	p_shader.start();

	glm::mat4 model = p_Model.getModelTransform();
	glm::mat4 view = p_viewMatrix;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 1000.0f);

	p_shader.setUniformMatrix4fv("v_uni_model", false, glm::value_ptr(model));
	p_shader.setUniformMatrix4fv("v_uni_view", false, glm::value_ptr(view));
	p_shader.setUniformMatrix4fv("v_uni_projection", false, glm::value_ptr(projection));

	// setup lighting
	glm::vec3 lightPos = p_light.position;
	glm::vec3 lightColor = p_light.color;
	p_shader.setUniform3fv("v_uni_lightPosition", glm::value_ptr(lightPos));
	p_shader.setUniformMatrix4fv("v_uni_viewMatrix", false,glm::value_ptr(p_viewMatrix));
	p_shader.setUniform3fv("f_uni_lightColor", glm::value_ptr(lightColor));
	p_shader.setUniform1i("f_uni_shineDamper", 15);
	p_shader.setUniform1f("f_uni_ambient", 0.1f);

	p_Model.bind();
	p_shader.setUniform1i("f_uni_texture", 0);
	glDrawElements(GL_TRIANGLES, p_Model.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
	p_Model.unbind();
	
	p_shader.stop();
}

void Renderer::drawSkybox(Skybox& p_skybox, glm::mat4 p_viewMatrix, ShaderProgram& p_shader) const
{
	glDepthFunc(GL_LEQUAL);
	//glDepthMask(GL_FALSE);
	p_shader.start();

	// double cast to remove last dimension (prevent translation)
	glm::mat4 view = glm::mat4(glm::mat3(p_viewMatrix));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 100.0f);

	p_shader.setUniformMatrix4fv("v_uni_view", false, glm::value_ptr(view));
	p_shader.setUniformMatrix4fv("v_uni_projection", false, glm::value_ptr(projection));

	// draw
	p_skybox.bind();
	p_shader.setUniform1i("f_uni_texture", 1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	p_skybox.unbind();

	p_shader.stop();
	//glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}

void Renderer::drawEM(Model& p_Model, glm::mat4 p_viewMatrix, ShaderProgram& p_shader, Skybox& p_skybox, Light& p_light) const
{
	p_shader.start();

	glm::mat4 model = p_Model.getModelTransform();
	glm::mat4 view = p_viewMatrix;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 1000.0f);

	p_shader.setUniformMatrix4fv("v_uni_model", false, glm::value_ptr(model));
	p_shader.setUniformMatrix4fv("v_uni_view", false, glm::value_ptr(view));
	p_shader.setUniformMatrix4fv("v_uni_projection", false, glm::value_ptr(projection));

	glm::vec3 lightPos = p_light.position;
	glm::vec3 lightColor = p_light.color;
	p_shader.setUniform3fv("v_uni_lightPosition", glm::value_ptr(lightPos));
	p_shader.setUniform3fv("f_uni_lightColor", glm::value_ptr(lightColor));
	p_shader.setUniform1f("f_uni_ambient", 0.1f);

	p_skybox.bind();
	p_Model.bind();
	p_shader.setUniform1i("f_uni_texture", 1);
	glDrawElements(GL_TRIANGLES, p_Model.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
	p_Model.unbind();
	p_skybox.unbind();

	p_shader.stop();
}

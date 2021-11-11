#include "Camera.h"

#include <algorithm>
#include <iostream>
#include <GLFW/glfw3.h>

Camera::Camera(): m_moveSpeed(0.8f), m_baseSpeed(0.5f), m_currentHRot(-90.0f), m_currentVRot(0.0f), m_sensitivity(0.05f)
{
	m_cPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_cFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_cUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

// this snippet is copied from LearnOpenGL
glm::mat4 Camera::getDemoRotatingCamera()
{
	const float radius = 5.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	return view;
}

glm::mat4 Camera::getCameraTransform()
{
	glm::mat4 view;
	view = glm::lookAt(m_cPos, m_cPos + m_cFront, m_cUp);
	return view;
}

void Camera::setDelta(float p_delta)
{
	m_moveSpeed = m_baseSpeed * p_delta;
}

void Camera::lookTo(float p_hRot, float p_vRot)
{
	m_currentHRot += p_hRot * m_sensitivity;
	m_currentVRot += p_vRot * m_sensitivity;
	
	// flip guard
	m_currentVRot = std::min(m_currentVRot, 89.0f);
	m_currentVRot = std::max(m_currentVRot, -89.0f);

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_currentHRot)) * cos(glm::radians(m_currentVRot));
	direction.y = sin(glm::radians(m_currentVRot));
	direction.z = sin(glm::radians(m_currentHRot)) * cos(glm::radians(m_currentVRot));
	m_cFront = glm::normalize(direction);
}


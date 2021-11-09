#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

const float CAMERA_SENSITIVITY = 0.1f;

class Camera
{
private:
	glm::vec3 m_cPos;
	glm::vec3 m_cFront;
	glm::vec3 m_cUp;
	
	float m_currentHRot;
	float m_currentVRot;

	float m_moveSpeed;
	float m_baseSpeed;
	float m_sensitivity;

public:
	Camera();
	~Camera();

	// returns the VIEW matrix
	glm::mat4 getDemoRotatingCamera();
	glm::mat4 getCameraTransform();

	void setDelta(float p_delta);

	// movements
	inline void moveUp() { m_cPos += m_moveSpeed * m_cUp; };
	inline void moveDown() { m_cPos -= m_moveSpeed * m_cUp; };
	inline void moveLeft() { m_cPos += m_moveSpeed * glm::normalize( glm::cross(m_cUp, m_cFront)); };
	inline void moveRight() { m_cPos -= m_moveSpeed * glm::normalize(glm::cross(m_cUp, m_cFront)); };
	inline void moveFront() { m_cPos += m_moveSpeed * m_cFront; };
	inline void moveBack() { m_cPos -= m_moveSpeed * m_cFront; };
	inline glm::vec3 getViewVector() { return m_cPos + m_cFront; };

	// look functions
	void lookTo(float p_hRot, float p_vRot);
};


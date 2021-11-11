#pragma once

#include <vector>
#include "Texture.h"
#include <glm/glm.hpp>

class Model
{
private:
	unsigned int m_id;
	std::string m_name;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;
	std::vector<unsigned int> m_vBufferIDs;
	std::vector<unsigned int> m_iBufferIDs;
	Texture* m_texture;

	glm::mat4 m_rotation;
	glm::vec3 m_rotInfo;
	glm::mat4 m_translation;
	glm::vec3 m_trInfo;

public:
	Model(const std::string& p_name);
	Model(const std::string& p_name, const std::string& p_filepath);
	~Model();

	inline unsigned int getId() const { return m_id; };
	inline unsigned int getVertexCount() const { return m_vertexCount; };
	inline unsigned int getIndexCount() const { return m_indexCount; };
	inline unsigned int getTextureId() const { if (m_texture) return m_texture->getId(); };
	inline glm::vec3 getRot() const { return m_rotInfo; };
	inline glm::vec3 getTranslation() const { return m_trInfo; };
	inline std::string getName() const { return m_name; };

	void bind() const;
	void unbind() const;
	void bindIndexBuffer(unsigned int* p_indices, unsigned int p_iCount);
	void addVertexAttr(float* p_vertices, unsigned int p_vSize, const std::string& p_texturePath);
	void addVertexAttr(float* p_vertices, unsigned int p_vSize);
	void rotate(float p_yaw, float p_pitch, float p_roll);
	void translate(float p_x, float p_y, float p_z);
	glm::mat4 getModelTransform();
	void clearTransform();

};


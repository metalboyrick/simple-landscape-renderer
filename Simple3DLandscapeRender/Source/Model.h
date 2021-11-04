#pragma once

#include <vector>
#include "Texture.h"

class Model
{
private:
	unsigned int m_id;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;
	std::vector<unsigned int> m_vBufferIDs;
	std::vector<unsigned int> m_iBufferIDs;
	Texture* m_texture;

public:
	Model();
	~Model();

	inline unsigned int getId() const { return m_id; };
	inline unsigned int getVertexCount() const { return m_vertexCount; };
	inline unsigned int getIndexCount() const { return m_indexCount; };
	inline unsigned int getTextureId() const { if (m_texture) return m_texture->getId(); };

	void bind() const;
	void unbind() const;
	void bindIndexBuffer(unsigned int* p_indices, unsigned int p_iCount);
	void addVertexAttr(float* p_vertices, unsigned int p_vSize, const std::string& p_texturePath);
	void addVertexAttr(float* p_vertices, unsigned int p_vSize);

};


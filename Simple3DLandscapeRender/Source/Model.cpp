#include "Model.h"

#include <GL/glew.h>
#include <OBJ_Loader/OBJ_Loader.h>
#include <pystring/pystring.h>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <algorithm>

Model::Model() : m_vertexCount(0), m_indexCount(0)
{
	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
	m_texture = nullptr;
}

Model::Model(const std::string& p_filepath)
{
	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
	m_texture = nullptr;

	// read from obj file
	objl::Loader loader;
	loader.LoadFile(p_filepath);

	// get the vertices and color and texture coordinates
	std::vector<float> vertexArray;
	std::vector<unsigned int> indices;

	unsigned int counter = 0;

	for (auto& mesh : loader.LoadedMeshes)
	{
		for (int i = 0; i < mesh.Vertices.size(); i++)
		{
			// position
			vertexArray.push_back(mesh.Vertices.at(i).Position.X);
			vertexArray.push_back(mesh.Vertices.at(i).Position.Y);
			vertexArray.push_back(mesh.Vertices.at(i).Position.Z);

			// color
			vertexArray.push_back(mesh.MeshMaterial.Kd.X);
			vertexArray.push_back(mesh.MeshMaterial.Kd.Y);
			vertexArray.push_back(mesh.MeshMaterial.Kd.Z);

			// texture coordinates
			vertexArray.push_back(mesh.Vertices.at(i).TextureCoordinate.X);
			vertexArray.push_back(mesh.Vertices.at(i).TextureCoordinate.Y);

			// normal
			vertexArray.push_back(mesh.Vertices.at(i).Normal.X);
			vertexArray.push_back(mesh.Vertices.at(i).Normal.Y);
			vertexArray.push_back(mesh.Vertices.at(i).Normal.Z);

			indices.push_back(static_cast<unsigned int>(counter));
			counter++;
		}
	}

	addVertexAttr(vertexArray.data(), vertexArray.size());
	bindIndexBuffer(indices.data(), indices.size());
}

Model::~Model()
{
	if (m_texture) delete m_texture;

	for (unsigned int id : m_vBufferIDs)
		glDeleteBuffers(1, &id);

	for (unsigned int id : m_iBufferIDs)
		glDeleteBuffers(1, &id);

	glDeleteVertexArrays(1, &m_id);
}

void Model::bind() const
{
	glBindVertexArray(m_id);
	if (m_texture)
		m_texture->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBufferIDs[0]);
}

void Model::unbind() const
{
	glBindVertexArray(0);
	if(m_texture)
		m_texture->unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::bindIndexBuffer(unsigned int* p_indices, unsigned int p_iCount)
{
	// create ibo + bind
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_iCount * sizeof(unsigned int), p_indices, GL_STATIC_DRAW);

	m_indexCount = p_iCount;
	m_iBufferIDs.push_back(ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::addVertexAttr(float* p_vertices, unsigned int p_vSize, const std::string& p_texturePath)
{
	// bind vertex array
	glBindVertexArray(m_id);

	
	// create vbo + bind
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, p_vSize * sizeof(float), p_vertices, GL_STATIC_DRAW);
	
	m_texture = new Texture(p_texturePath);
	m_vertexCount = p_vSize / 11;

	// add attribute to be drawn
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	
	// store the id
	m_vBufferIDs.push_back(vbo);
	
	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::addVertexAttr(float* p_vertices, unsigned int p_vSize)
{
	// bind vertex array
	glBindVertexArray(m_id);

	// create vbo + bind
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, p_vSize * sizeof(float), p_vertices, GL_STATIC_DRAW);

	m_vertexCount = p_vSize / 11;

	// add attribute to be drawn
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// store the id
	m_vBufferIDs.push_back(vbo);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


#pragma once
class Skybox
{
private:
	unsigned int m_ibo;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_texture;

public:
	Skybox();
	~Skybox();

	void bind() const;
	void unbind() const;
};


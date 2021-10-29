#include "Texture.h"

#include <stb_image/stb_image.h>
#include <GL/glew.h>

Texture::Texture(const std::string& p_filepath)
{
	// generate and bind the texture buffer
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load the file
	unsigned char* imageData = stbi_load(p_filepath.c_str(), &m_width, &m_height, &m_channelNumber, 0);
	if (imageData)
	{
		// load the image to the texture buffer
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// free the image buffer
	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

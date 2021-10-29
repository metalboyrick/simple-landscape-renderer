#pragma once

#include <string>

class Texture
{
private:
	unsigned int m_id;
	int m_width;
	int m_height;
	int m_channelNumber;

public:
	Texture(const std::string& p_filepath);
	~Texture();

	void bind() const;
	void unbind() const;

	inline unsigned int getId() const { return m_id; };

};


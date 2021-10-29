#pragma once

#include <string>

class ShaderProgram
{
private:
	unsigned int m_id;

public:
	ShaderProgram(const std::string& p_vertexShaderPath, const std::string& p_fragmentShaderPath);
	~ShaderProgram();

	void start() const;
	void stop() const;
	void setUniform4f(const std::string& p_name, float p_x, float p_y, float p_z, float p_a) const;
	void setUniform1i(const std::string& p_name, int p_param);
	void setUniformMatrix4fv(const std::string& p_name, bool p_isTranspose, float* p_matrix);

private:
	std::string parseShader(const std::string& filename);
	unsigned int compileShader(unsigned int type, const std::string& source);

};


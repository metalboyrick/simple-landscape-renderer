#include "ShaderProgram.h"

#include <GL/glew.h>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& p_vertexShaderPath, const std::string& p_fragmentShaderPath)
{
	std::string vertexShaderSource = parseShader(p_vertexShaderPath);
	std::string fragmentShaderSource = parseShader(p_fragmentShaderPath);
	
	// boilerplate: creates the program instance
	unsigned int program = glCreateProgram();

	// get the vertex shader and the fragment shader
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// attach the shaders + linking and validation
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	// shader intermediate cleanup
	glDeleteShader(vs);
	glDeleteShader(fs);

	m_id = program;
}

ShaderProgram::~ShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(m_id);
}

void ShaderProgram::start() const
{
	glUseProgram(m_id);
}

void ShaderProgram::stop() const
{
	glUseProgram(0);
}

void ShaderProgram::setUniform3fv(const std::string& p_name, float* p_vec) const
{
	int uniformLocation = glGetUniformLocation(m_id, p_name.c_str());
	if (uniformLocation > -1)
	{
		glUniform3fv(uniformLocation, 1, p_vec);
	}
}

void ShaderProgram::setUniform1i(const std::string& p_name, int p_param)
{
	int uniformLocation = glGetUniformLocation(m_id, p_name.c_str());
	if (uniformLocation > -1)
	{
		glUniform1i(uniformLocation, p_param);
	}
}

void ShaderProgram::setUniformMatrix4fv(const std::string& p_name, bool p_isTranspose, float* p_matrix)
{
	int uniformLocation = glGetUniformLocation(m_id, p_name.c_str());
	unsigned int isTranspose = p_isTranspose ? GL_TRUE : GL_FALSE;
	if (uniformLocation > -1)
	{
		glUniformMatrix4fv(uniformLocation, 1, isTranspose, p_matrix);
	}
}

void ShaderProgram::setUniform4f(const std::string& p_name, float p_x, float p_y, float p_z, float p_a) const
{
	int uniformLocation = glGetUniformLocation(m_id, p_name.c_str());
	if (uniformLocation > -1)
	{
		glUniform4f(uniformLocation, p_x, p_y, p_z, p_a);
	}
}

std::string ShaderProgram::parseShader(const std::string& filename)
{
	std::fstream inFile;
	inFile.open(filename, std::ios::out | std::ios::in);

	std::string line;
	std::string finalOutput = "";
	while (getline(inFile, line))
	{
		finalOutput += (line + "\n");
	}

	return finalOutput;
}

unsigned int ShaderProgram::compileShader(unsigned int type, const std::string& source)
{
	// get the id of the shader type
	unsigned int shaderID = glCreateShader(type);

	// load the shader source code (parse to the c string)
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);

	// compile the shader
	glCompileShader(shaderID);

	// error handling
	int compileResult;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		// query the needed stuff
		int errLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errLength);
		char* message = new char[errLength];
		glGetShaderInfoLog(shaderID, errLength, &errLength, message);

		// print the errors
		std::cerr << "ERROR: Fail to compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << " !" << std::endl;
		std::cerr << message << std::endl;

		// delete the shader
		glDeleteShader(shaderID);

		// delete the message since it is dynamically allocated
		delete[] message;

		return 0;
	}


	return shaderID;
}

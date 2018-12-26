#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLEW/glew.h>
#include <GLM/gtc/type_ptr.hpp>
std::string Shader::GetShaderCode(const char * ShaderSourcePath)
{
	std::string __shader_source_code_;
	std::stringstream __shader_source_stream_;
	try {
		
		std::ifstream __shader_stream_(ShaderSourcePath);
		__shader_stream_.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		__shader_source_stream_ << __shader_stream_.rdbuf();
		__shader_source_code_ = __shader_source_stream_.str();
	}
	catch (std::ifstream::failure fail)
	{
		std::cerr << "ERROR::CANNOT_READ_THE_SHADER_FILE\n";
	}
	return __shader_source_code_;
}

unsigned int Shader::GetShaderID(unsigned int ShaderType, const char * ShaderSourceCode)
{
	unsigned int __shader_id = glCreateShader(ShaderType);
	glShaderSource(__shader_id, 1, &ShaderSourceCode, NULL);
	glCompileShader(__shader_id);
	int CompileStat = 0;
	glGetShaderiv(__shader_id, GL_COMPILE_STATUS, &CompileStat);
	if (CompileStat == GL_FALSE)
	{
		int __info_log_length = 0;
		glGetShaderiv(__shader_id, GL_INFO_LOG_LENGTH, &__info_log_length);
		char * __error_mesage = new char[__info_log_length];
		glGetShaderInfoLog(__shader_id, __info_log_length, &__info_log_length, __error_mesage);
		std::cerr << "ERROR::FAILED_TO_COMPILE_" << ((ShaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << "_SHADER!!!\nERROR::MESSAGE - \" "<< __error_mesage << "\"\n";
		delete __error_mesage;
	}
	return __shader_id;
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderProgramID);
}
void Shader::CompileShader(const char * VertexShaderCode, const char * FragmentShaderCode)
{
	std::cout << VertexShaderCode << std::endl << FragmentShaderCode << std::endl;
	m_ShaderProgramID = glCreateProgram();
	unsigned int __vertex_shader_id_ = GetShaderID(GL_VERTEX_SHADER, VertexShaderCode);
	unsigned int __fragment_shader_id_ = GetShaderID(GL_FRAGMENT_SHADER, FragmentShaderCode);
	glAttachShader(m_ShaderProgramID, __vertex_shader_id_);
	glAttachShader(m_ShaderProgramID, __fragment_shader_id_);
	glLinkProgram(m_ShaderProgramID);
	glValidateProgram(m_ShaderProgramID);

	int CompileStat = 1;
	glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &CompileStat);
	if (CompileStat != GL_TRUE)
	{
		int InfoLogLength = 1024;
		glGetProgramiv(m_ShaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		char * ErrorMessage = new char[InfoLogLength];
		glGetProgramInfoLog(m_ShaderProgramID, InfoLogLength, &InfoLogLength, ErrorMessage);
		printf("ERROR::SHADER<->PROGRAM::LINKING_FAILED!!!\nERROR::MESSAGE!!!\n%s\n", ErrorMessage);
		delete ErrorMessage;
	}
	glDeleteShader(__vertex_shader_id_);
	glDeleteShader(__fragment_shader_id_);
}
void Shader::SetResourceAndCompile(std::string & VertexShaderCode, std::string & FragmentShaderCode)
{
	const char * vsc = VertexShaderCode.c_str();
	const char * fsc = FragmentShaderCode.c_str();
	CompileShader(vsc, fsc);
}

void Shader::SetResourceAndCompile(const char * VertexShaderCode, const char * FragmentShaderCode)
{
	CompileShader(VertexShaderCode, FragmentShaderCode);
}

void Shader::SetResourcePathAndCompile(const char * VertexShaderPath, const char * FragmentShaderPath)
{
	std::string __vertex_shader_code = GetShaderCode(VertexShaderPath);
	std::string __fragment_shader_code = GetShaderCode(FragmentShaderPath);
	SetResourceAndCompile(__vertex_shader_code, __fragment_shader_code);
}

int Shader::GetUniformLocation(std::string & UniformName)
{
	if (m_UniformLocationCache.find(UniformName) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[UniformName];
	}
	const char * __uniform_name_ = UniformName.c_str();
	int __uniform_location = glGetUniformLocation(m_ShaderProgramID, __uniform_name_);
	m_UniformLocationCache[UniformName] = __uniform_location;
	if (__uniform_location == -1)
		std::cerr << "ERROR::SPECIFIED_UNIFORM_NAME_NOT_FOUND (\" " <<  UniformName << " \") !!!\n";
	return __uniform_location;
}

void Shader::SetUniform(std::string & UniformName, int Value) { glUniform1i(GetUniformLocation(UniformName), Value); }
void Shader::SetUniform(std::string & UniformName, float Value) { glUniform1f(GetUniformLocation(UniformName), Value); }
void Shader::SetUniform(std::string & UniformName, double Value) { glUniform1d(GetUniformLocation(UniformName), Value); }

void Shader::SetUniform(std::string & UniformName, int v1, int v2) { glUniform2i(GetUniformLocation(UniformName), v1, v2); }
void Shader::SetUniform(std::string & UniformName, float v1, float v2) { glUniform2f(GetUniformLocation(UniformName), v1, v2); }
void Shader::SetUniform(std::string & UniformName, double v1, double v2) { glUniform2d(GetUniformLocation(UniformName), v1, v2); }
void Shader::SetUniform(std::string & UniformName, glm::vec2 & v) { glUniform2f(GetUniformLocation(UniformName), v.x, v.y); }

void Shader::SetUniform(std::string & UniformName, int v1, int v2, int v3) { glUniform3i(GetUniformLocation(UniformName), v1, v2, v3); }
void Shader::SetUniform(std::string & UniformName, float v1, float v2, float v3) { glUniform3f(GetUniformLocation(UniformName), v1, v2, v3); }
void Shader::SetUniform(std::string & UniformName, double v1, double v2, double v3) { glUniform3d(GetUniformLocation(UniformName), v1, v2, v3); }
void Shader::SetUniform(std::string & UniformName, glm::vec3 & v) { glUniform3f(GetUniformLocation(UniformName), v.x, v.y, v.z); }

void Shader::SetUniform(std::string & UniformName, int v1, int v2, int v3, int v4) { glUniform4i(GetUniformLocation(UniformName), v1, v2, v3, v4);  }
void Shader::SetUniform(std::string & UniformName, float v1, float v2, float v3, float v4){ glUniform4f(GetUniformLocation(UniformName), v1, v2, v3, v4);  }
void Shader::SetUniform(std::string & UniformName, double v1, double v2, double v3, double v4){ glUniform4d(GetUniformLocation(UniformName), v1, v2, v3, v4); }
void Shader::SetUniform(std::string & UniformName, glm::vec4 & v) { glUniform4f(GetUniformLocation(UniformName), v.x, v.y, v.z, v.w); }

void Shader::SetUniform(std::string & UniformName, glm::mat2x2 & MatrixValue) { glUniformMatrix2fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }
void Shader::SetUniform(std::string & UniformName, glm::mat2x3 & MatrixValue) { glUniformMatrix2x3fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }
void Shader::SetUniform(std::string & UniformName, glm::mat2x4 & MatrixValue) { glUniformMatrix2x4fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }

void Shader::SetUniform(std::string & UniformName, glm::mat3x2 & MatrixValue) { glUniformMatrix3x2fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }
void Shader::SetUniform(std::string & UniformName, glm::mat3x3 & MatrixValue) { glUniformMatrix3fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }
void Shader::SetUniform(std::string & UniformName, glm::mat3x4 & MatrixValue) { glUniformMatrix3x4fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }

void Shader::SetUniform(std::string & UniformName, glm::mat4x2 & MatrixValue) { glUniformMatrix4x2fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }
void Shader::SetUniform(std::string & UniformName, glm::mat4x3 & MatrixValue) { glUniformMatrix4x3fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }
void Shader::SetUniform(std::string & UniformName, glm::mat4x4 & MatrixValue) { glUniformMatrix4fv(GetUniformLocation(UniformName), 1, GL_FALSE, glm::value_ptr(MatrixValue)); }


void Shader::printLocationCache()
{
}

void Shader::BindShaderProgram()
{
	glLinkProgram(m_ShaderProgramID);
	glUseProgram(m_ShaderProgramID);
	glValidateProgram(m_ShaderProgramID);
}

void Shader::UnBindShaderProgram()
{
	glUseProgram(0);
}
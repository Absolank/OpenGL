#pragma once
#include <GLM/glm.hpp>
#include <unordered_map>
class Shader
{
	unsigned int m_ShaderProgramID = 0;
	std::unordered_map <std::string, int> m_UniformLocationCache;
	std::string GetShaderCode(const char * ShaderSourcePath);
	unsigned int GetShaderID(unsigned int ShaderType, const char * ShaderSourceCode);
	void CompileShader(const char * VertexShaderCode, const char * FragmentShaderCode);
public:
	~Shader();

	void SetResourceAndCompile(std::string& VertexShaderCode, std::string& FragmentShaderCode);
	void SetResourceAndCompile(const char * VertexShaderCode, const char * FragmentShaderCode);
	void SetResourcePathAndCompile(const char * VertexShaderPath, const char * FragmentShaderPath);

	int GetUniformLocation(std::string& UniformName);

	void SetUniform(std::string& UniformName, int Value);
	void SetUniform(std::string& UniformName, float Value);
	void SetUniform(std::string& UniformName, double Value);

	void SetUniform(std::string& UniformName, int v1, int v2);
	void SetUniform(std::string& UniformName, float v1, float v2);
	void SetUniform(std::string& UniformName, double v1, double v2);
	void SetUniform(std::string& UniformName, glm::vec2& v);

	void SetUniform(std::string& UniformName, int v1, int v2, int v3);
	void SetUniform(std::string& UniformName, float v1, float v2, float v3);
	void SetUniform(std::string& UniformName, double v1, double v2, double v3);
	void SetUniform(std::string& UniformName, glm::vec3& v);

	void SetUniform(std::string& UniformName, int v1, int v2, int v3, int v4);
	void SetUniform(std::string& UniformName, float v1, float v2, float v3, float v4);
	void SetUniform(std::string& UniformName, double v1, double v2, double v3, double v4);
	void SetUniform(std::string& UniformName, glm::vec4& v);

	void SetUniform(std::string& UniformName, glm::mat2x2& MatrixValue);
	void SetUniform(std::string& UniformName, glm::mat2x3& MatrixValue);
	void SetUniform(std::string& UniformName, glm::mat2x4& MatrixValue);

	void SetUniform(std::string& UniformName, glm::mat3x2& MatrixValue);
	void SetUniform(std::string& UniformName, glm::mat3x3& MatrixValue);
	void SetUniform(std::string& UniformName, glm::mat3x4& MatrixValue);
	
	void SetUniform(std::string& UniformName, glm::mat4x2& MatrixValue);
	void SetUniform(std::string& UniformName, glm::mat4x3& MatrixValue);
	void SetUniform(std::string& UniformName, glm::mat4x4& MatrixValue);

	void printLocationCache();
	void BindShaderProgram();
	void UnBindShaderProgram();

};


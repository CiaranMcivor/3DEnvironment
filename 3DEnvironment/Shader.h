#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>
#include "Transform.h"
#include "Camera.h"


class Shader
{
public:
	Shader();
	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	void init(const std::string& vertFile, const std::string& fragFile);
	void init(const std::string& vertFile, const std::string& fragFile,const std::string& geometryFile);

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	~Shader();

	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		//if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//
	}

protected:
private:
	static const unsigned int NUM_SHADERS = 3; // number of shaders
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};
	GLuint shaderProgram; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};


#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glad/glad.h>

struct Shader {
	unsigned int ID;

	Shader() {};

	void UseShader() {
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	Shader(std::string vertFilePath, std::string fragFilePath) {
		std::string vertexShaderCode;
		std::string fragShaderCode;

		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertFilePath);
			fShaderFile.open(fragFilePath);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexShaderCode = vShaderStream.str();
			fragShaderCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexShaderCode.c_str();
		const char* fShaderCode = fragShaderCode.c_str();

		unsigned int vertShader;
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vShaderCode, NULL);
		glCompileShader(vertShader);

		// Error Check Fragment Shader
		{
			int success;
			char log[512];
			glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertShader, 512, NULL, log);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
			}
		}

		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fShaderCode, NULL);
		glCompileShader(fragShader);

		// Error Check Fragment Shader
		{
			int success;
			char log[512];
			glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fragShader, 512, NULL, log);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
			}
		}

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);

		// Error Check Shader Program
		{
			int success;
			char log[512];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderProgram, 512, NULL, log);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
			}
		}
		
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		ID = shaderProgram;
	}

};
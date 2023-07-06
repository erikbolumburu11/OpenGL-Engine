#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glad/glad.h>

struct Shader {
	unsigned int ID;

	Shader() {};
	Shader::Shader(std::string vertFilePath, std::string fragFilePath);

	void UseShader();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;


};
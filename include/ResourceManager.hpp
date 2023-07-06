#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <Shader.hpp>

class ResourceManager {
public:
	std::unordered_map<std::string, Shader> shaderPrograms;
};

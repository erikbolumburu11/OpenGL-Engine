#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <Material.hpp>
#include <Shader.hpp>

class ResourceManager {
public:
	std::unordered_map<std::string, Material> materials;
};

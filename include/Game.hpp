#pragma once
#include "ResourceManager.hpp"
#include <Renderer.hpp>
class Game {
public:
	ResourceManager resourceManager;
	Renderer renderer;
	float deltaTime = 0.0f;
};
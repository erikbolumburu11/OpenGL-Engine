#include <iostream>
#include "LightManager.hpp"

LightManager::LightManager(entt::registry& registry){
    for (int i = 0; i < UPPER_POINT_LIGHT_LIMIT; i++)
    {
        entt::entity pointLightEntity = registry.create();
        Components::Lights::PointLight& light = registry.emplace<Components::Lights::PointLight>(pointLightEntity,
            false,
            1.0f, 0.22f, 0.20f,
            glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)
        );
        Components::Transform& transform = registry.emplace<Components::Transform>(pointLightEntity, 
            glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f)
        );
    }
}

void LightManager::CreatePointLight(entt::registry& registry, Components::Lights::PointLight lightData, Components::Transform transform)
{
    entt::entity availableLight;

	auto pointLights = registry.view<Components::Lights::PointLight>();
	pointLights.each([&](Components::Lights::PointLight& pointLight){
        if(!pointLight.active) availableLight = entt::to_entity(registry, pointLight);
    });

    if(availableLight == entt::null){
        std::cout << "No Free Lights!" << std::endl;
        return;
    }

    Components::Lights::PointLight& pl = registry.get<Components::Lights::PointLight>(availableLight);
    Components::Transform& t = registry.get<Components::Transform>(availableLight);

    pl.constant = lightData.constant;
    pl.linear = lightData.linear;
    pl.quadratic = lightData.quadratic;

    pl.ambient = lightData.ambient;
    pl.diffuse = lightData.diffuse;
    pl.specular = lightData.specular;
    pl.active = true;

    t.pos = transform.pos;
    t.rot = transform.rot;
    t.scale = transform.scale;
}

void LightManager::DestroyPointLight(entt::registry& registry, entt::entity pointLightEntity)
{
    Components::Lights::PointLight& pl= registry.get<Components::Lights::PointLight>(pointLightEntity);
    pl.active = false;
    pl.constant = 0;
    pl.linear = 0;
    pl.quadratic = 0;
}

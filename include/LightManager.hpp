#include <constants.hpp>
#include <entt/entt.hpp>
#include <Components/Light.hpp>
#include <Components/Transform.hpp>

struct LightManager {
public:
    LightManager(entt::registry& registry);

    void CreatePointLight(entt::registry& registry, Components::Lights::PointLight LightData, Components::Transform transform);
    void DestroyPointLight(entt::registry& registry, entt::entity pointLightEntity);
};
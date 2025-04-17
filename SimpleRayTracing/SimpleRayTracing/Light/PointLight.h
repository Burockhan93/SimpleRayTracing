#pragma once
#include "Light.h"

class PointLight : public Light {
private:
	Vec3 m_position{};
public:
	PointLight() = default;
	PointLight(Vec3 color, Vec3 position, double intensity);
	PointLight(const PointLight& other);
	PointLight& operator=(const PointLight& other);

	// getter
	Vec3 get_position();

	//overrides
	Vec3 get_direction(const Hit& hit) override;
	Vec3 get_intensity(const Hit& hit, World& world) override;
	bool shadow_hit(const Ray& ray, World& world)override;
};

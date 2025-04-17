#pragma once
#include "Light.h"
#include "..\Utils\Sampler.h"
#include "..\Math\Vec3.h"
class Object;
class AreaLight : public Light {
private:
	Object* m_object;
	Vec3 m_direction{};
	Vec3 m_normal{};
	Vec3 m_samplePoint{};
public:
	//constructors
	AreaLight();
	AreaLight(Object* object, Vec3 color, double intensity);
	AreaLight(const AreaLight& other);

	//copy asisgment op
	AreaLight& operator=(const AreaLight& other);

	//methods
	Vec3 get_direction(const Hit& hit)override;
	Vec3 get_intensity(const Hit& hit, World& world)override;
	bool shadow_hit(const Ray& ray, World& world)override;

};
#pragma once
#include "Light.h"
#include "..\Utils\Sampler.h"
#include "..\Math\Vec3.h"

class AmbientLight : public Light {
private:
	double m_factor{};
	Sampler m_sampler{};
public:
	//constructors
	AmbientLight();
	AmbientLight(double factor, Vec3 color, double intensity);
	AmbientLight(const AmbientLight& other);

	//copy asisgment op
	AmbientLight& operator=(const AmbientLight& other);

	//methods
	Vec3 get_direction(const Hit& hit)override;
	Vec3 get_intensity(const Hit& hit, World& world)override;
	bool shadow_hit(const Ray& ray, World& world)override ;

};
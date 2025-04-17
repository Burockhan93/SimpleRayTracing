#pragma once
#include "Vec3.h"
class Ray {
private:
public:
	//members
	Vec3 m_origin{};
	Vec3 m_direction{};
	//constructors
	Ray() = default;
	Ray(Vec3 origin, Vec3 direction);
	Ray(const Ray& ray);
	~Ray() = default;
	//copy assignment

	Ray& operator=(const Ray& ray);

};

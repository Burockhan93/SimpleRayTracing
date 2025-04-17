#pragma once
#include "Object.h"
#include "..\Math\Constants.h"
#include "..\Utils\Sampler.h"

class Sphere : public Object {
private:
	Sampler m_sampler{};
	Vec3 m_center{};
	double m_radius{};
public:

	//constructors

	Sphere();
	Sphere(Vec3 origin, double radius, Material* material);
	Sphere(Vec3 origin, double radius);
	Sphere(const Sphere& sphere);
	~Sphere() = default;

	//copy assignment

	Sphere& operator=(const Sphere& other) {
		if (this == &other)
			return *this;
		Object::operator=(other);
		m_center = other.m_center;
		m_radius = other.m_radius;
	}

	//methods
	bool solve_quadratic(const float& a, const float& b, const float& c,float& x0, float& x1);
	Vec3 get_sample();
	double get_pdf() override;
	Vec3 get_normal(const Vec3& point) override;
	Box calculate_bb() override;
	bool ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) override;


};

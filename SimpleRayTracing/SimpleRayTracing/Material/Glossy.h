#pragma once
#include <iostream>
#include "BRDF.h"

class Glossy : BRDF<Material> {
public:
	double m_exponent{};
	double m_reflectance{};
	Vec3 m_color{};

	//constructors
	Glossy();
	Glossy(double factor, double exp, Vec3 color);
	Glossy(double factor, Vec3 color);
	~Glossy() = default;

	//methods
	Vec3 f(const Hit& hit, Vec3& wi, const Vec3& wo)override;
	Vec3 sample_f(Material* mat, const Hit& hit, const Vec3& wo)override;
	double pdf(Material* mat, const Hit& hit, const Vec3& wi, const Vec3& wo)override;
	Vec3 eval(Material* mat, const Hit& hit, const Vec3& wi, const Vec3& wo)override;
	Vec3 color() override;
	Glossy& operator=(const Glossy& other);


};

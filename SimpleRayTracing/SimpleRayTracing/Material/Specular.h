#pragma once

#include "BRDF.h"

class Specular : BRDF<Material> {
public:
	double m_exponent{};
	double m_reflectance{};
	Vec3 m_color{};

	//constructor
	Specular();
	~Specular()=default;
	Specular(double ref_factor, double exponent, Vec3 color);
	Specular(double ref_factor, Vec3 color);

	//overrides
	Vec3 color()override;
	Vec3 f(const Hit& hit, Vec3& wi, const Vec3& wo) override;
	Vec3 sample_f(Material* mat, const Hit& hit, const Vec3& wo)override;
	Vec3 eval(Material* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) override;
	double pdf(Material* mat, const Hit& hit, Vec3 const& wi, Vec3 const& wo)override;
};
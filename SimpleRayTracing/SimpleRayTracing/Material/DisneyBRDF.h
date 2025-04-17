#pragma once
#include "BRDF.h"
#include "Disney.h"
#include "..\Math\Constants.h"
#include "..\Math\MathUtils.h"

class DisneyBRDF : public BRDF<Disney> {
public:
	DisneyBRDF() = default;
	~DisneyBRDF() = default;
	
	Vec3 sample_f(Disney* mat, const Hit& hit, const Vec3& wo) override;
	Vec3 eval(Disney* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) override;
	double pdf(Disney* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) override;


	double fresnel(double cosT);
	double GTR1(double cosT, double a);
	double GTR2(double cosT, double a);
	double GGX(double cosT, double a);
	double k(double a, double y);
	DisneyBRDF& operator= (const DisneyBRDF& d);
};

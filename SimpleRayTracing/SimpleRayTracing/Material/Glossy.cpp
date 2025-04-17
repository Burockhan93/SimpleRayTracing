#include "Glossy.h"

Glossy::Glossy():m_reflectance{1.0},m_color{1,1,1}{}
Glossy::Glossy(double factor, double exp, Vec3 color)
	:m_reflectance{ factor }, m_exponent{ exp }, m_color{ color } {}
Glossy::Glossy(double factor, Vec3 color): m_reflectance{factor},m_color{color}{}

Vec3 Glossy::f(const Hit& hit, Vec3& wi, const Vec3& wo) {
	Vec3 r = wi.neg() + hit.m_normal * wi.dot(hit.m_normal * 2);
	double RdotV = std::max(0.0, r.dot(wo));
	return m_color * m_reflectance * std::pow(RdotV, 2);
}

Vec3 Glossy::sample_f(Material* mat, const Hit& hit, const Vec3& wo) {
	double NdotWo = hit.m_normal.dot(wo);
	Vec3 w = wo.neg() + hit.m_normal * 2 * NdotWo;

	Vec3 u = Vec3(0.00424, 1, 0.00764).cross(w).normalize();
	Vec3 v = u.cross(w);
	Vec3 point = m_sampler.hemisphere_sample(m_exponent);
	Vec3 wi{};
	if(hit.m_normal.dot(wi)<0) // z burda eksi olablr
		wi = u * -point.x + v * -point.y + w * point.z;
	else
		wi = u * point.x + v * point.y + w * point.z;

	return wi.normalize();

}
double Glossy::pdf(Material* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) {
	double NdotWo = hit.m_normal.dot(wo);
	Vec3 r = wo.neg() + hit.m_normal * 2 * NdotWo;
	double lobe = std::pow(r.dot(wi), m_exponent);
	return lobe * (hit.m_normal.dot(wi));
}
Vec3 Glossy::eval(Material* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) {
	double ndotwo = hit.m_normal.dot(wo);
	Vec3 r = wo.neg() + hit.m_normal * 2 * ndotwo;
	double lobe = std::pow(r.dot(wi), m_exponent);
	return m_color * m_reflectance * lobe;
}

Vec3 Glossy::color() {
	return m_color * m_reflectance;
}

Glossy& Glossy::operator=(const Glossy& other) {
	if (this == &other)
		return *this;

	BRDF::operator=(other);
	m_reflectance = other.m_reflectance;
	m_color = other.m_color;
	return *this;
}
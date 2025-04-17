#include "Specular.h"

Specular::Specular():m_exponent { 0 }, m_reflectance{ 1 }, m_color{}{}
Specular::Specular(double ref_factor, double exponent, Vec3 color) : m_reflectance{ ref_factor }, m_exponent{ exponent }, m_color{ color } {}
Specular::Specular(double ref_factor, Vec3 color) : m_reflectance{ ref_factor }, m_exponent{ 0 }, m_color{ color } {}

Vec3 Specular::color(){
	return m_reflectance * m_color;
}
Vec3 Specular::f(const Hit& hit, Vec3& wi, const Vec3& wo){
	return Vec3{};
}
Vec3 Specular::sample_f(Material* mat, const Hit& hit, const Vec3& wo){
	Vec3 sample = hit.m_direction - (hit.m_normal) * 2 * hit.m_direction.dot(hit.m_normal);
	return sample;
}
Vec3 Specular::eval(Material* mat, const Hit& hit, const Vec3& wi, const Vec3& wo) {
	return m_reflectance * m_color;
}
double Specular::pdf(Material* mat, const Hit& hit, Vec3 const& wi, Vec3 const& wo) {
	return hit.m_normal.dot(wi);
}

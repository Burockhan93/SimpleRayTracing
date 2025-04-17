#include "PointLight.h"

PointLight::PointLight(Vec3 color, Vec3 position, double intensity) :Light{ color,intensity }, m_position{ position } {}
PointLight::PointLight(const PointLight& other) {
	m_color = other.m_color;
	m_intensity = other.m_intensity;
}
PointLight& PointLight::operator=(const PointLight& other) {
	if (this == &other)
		return *this;
	m_color = other.m_color;
	m_intensity = other.m_intensity;
	return *this;
}
Vec3 PointLight::get_position() {
	return m_position;
}
Vec3 PointLight::get_direction(const Hit& hit) {
	
	return (m_position-hit.m_hitPoint).normalize();

}
Vec3 PointLight::get_intensity(const Hit& hit, World& world) {
	double distance = ( m_position- hit.m_hitPoint).length();
	double intense_factor = 1 / (distance * distance);
	return m_color * distance * intense_factor;

}
bool PointLight::shadow_hit(const Ray& ray, World& world) {
	double t;
	double maxt = (m_position - ray.m_origin).length();
	Vec3 intersection;
	Vec3 normal;
	for (Object* obj : world.m_objects) {
		if (obj->ray_intersects(ray, intersection, t, normal) && obj->get_shadowCast()) {
			if (t < maxt) {
				return true;
			}
		}
	}
	return false;
}

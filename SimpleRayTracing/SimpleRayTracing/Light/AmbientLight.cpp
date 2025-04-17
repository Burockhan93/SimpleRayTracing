#include "AmbientLight.h"
#include "..\Math\Constants.h"

AmbientLight::AmbientLight() :Light{} {}
AmbientLight::AmbientLight(double factor, Vec3 color, double intensity) :
	Light{ color, intensity }, m_factor{ factor } {
}
AmbientLight::AmbientLight(const AmbientLight& other) {
	m_intensity = other.m_intensity;
	m_color = other.m_color;
	m_factor = other.m_factor;
}
AmbientLight& AmbientLight::operator=(const AmbientLight& other) {

	if (this == &other)
		return *this;
	Light::operator=(other);
	m_factor = other.m_factor;
	return *this;
}

Vec3 AmbientLight::get_direction(const Hit& hit) {
	Vec3 w = hit.m_normal;//upward
	Vec3 u{};//u sifir cikmasin diye w nin paralel olmadigi axisi secioz dik axis ararken
	if (w.y > 1 - Constants::kEPSILON) {
		u = Vec3{ 0,0,1 }.cross(w).normalize();
	}
	else {
		u = Vec3{ 0,1,0 }.cross(w).normalize();
	}
	Vec3 v = u.cross(w).normalize();
	Vec3 point = m_sampler.hemisphere_sample(0.1);
	//weighted sum
	Vec3 ws = u * point.x + v * point.y + w * point.z;
	return ws.normalize();
}
Vec3 AmbientLight::get_intensity(const Hit& hit, World& world) {
	Ray shadow_ray(hit.m_hitPoint, get_direction(hit));
	if (shadow_hit(shadow_ray, world)) {
		return m_color * m_intensity * m_factor;
	}
	return m_color * m_intensity;
}
bool AmbientLight::shadow_hit(const Ray& ray, World& world)
{
	double t;
	Vec3 intersection{};
	Vec3 normal;
	for (Object* obj : world.m_objects) {
		if (obj->ray_intersects(ray, intersection, t, normal) && obj->get_shadowCast()) {
			return true;
		}
	}
	return false;
}
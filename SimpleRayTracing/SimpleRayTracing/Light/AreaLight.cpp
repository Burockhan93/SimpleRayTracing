#include "AreaLight.h"
#include "..\Utils\Hit.h"
class Object;

AreaLight::AreaLight() :Light{} {}
AreaLight::AreaLight(Object* object, Vec3 color, double intensity) :Light{ color,intensity }, m_object{ object } {}
AreaLight::AreaLight(const AreaLight& other) :Light{other} {}
//Thi metho needs some work
Vec3 AreaLight::get_direction(const Hit& hit) {
	m_samplePoint = m_object->get_sample();
	m_normal = m_object->get_normal(m_samplePoint);
	m_direction = (m_samplePoint - hit.m_hitPoint).normalize();

	return m_direction;

}
Vec3 AreaLight::get_intensity(const Hit& hit, World& world) {
    double ddotn = m_direction.neg().dot(m_normal);
    if (ddotn < 0) {
        return Vec3{0};
    }
    double d = (m_samplePoint - hit.m_hitPoint).length();
    double G = ddotn / (d * d);
    return (m_color * m_intensity * G) / m_object->get_pdf();
}
bool AreaLight::shadow_hit(const Ray& ray, World& world) {
    double t;
    double maxt = (m_samplePoint - ray.m_origin).length();
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
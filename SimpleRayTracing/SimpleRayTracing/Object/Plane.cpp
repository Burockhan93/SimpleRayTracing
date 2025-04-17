#include "Plane.h"
#include "..\Math\Constants.h"

Plane::Plane(): Object{}{}
Plane::Plane(Vec3 pos, Vec3 normal, Material* material):
	Object{material}, m_pos{pos},m_normal{normal.normalize()} { }
Plane::Plane(Vec3 pos, Vec3 normal):
	Object{}, m_pos{pos}, m_normal{normal.normalize()} { }
Plane::Plane(const Plane& other): 
	Object{ other.get_shader() }, m_pos{ other.m_pos }, m_normal{
	other.m_normal } {}

Box Plane::calculate_bb() { return Box{}; }

bool Plane::ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) {
	//Same as rectangle
	float t = Vec3{ m_pos - ray.m_origin }.dot(m_normal) / (ray.m_direction.dot(m_normal));

	if (t <= Constants::kEPSILON) {
		return false;
	}
	tmin = t;
	intersection = ray.m_origin + ray.m_direction * t;
	normal = m_normal;
	return true;
}
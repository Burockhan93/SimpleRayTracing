#include "Triangle.h"
#include "..\Math\Constants.h"

Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3)
	:m_v0{ p1 }, m_v1{ p2 }, m_v2{ p3 }, Object{} {
	m_normal = ((p2 - p1).cross(p3 - p1)).normalize();
}
Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Material* material)
	:m_v0{ p1 }, m_v1{ p2 }, m_v2{ p3 }, Object{ material } {
	m_normal = ((p2 - p1).cross(p3 - p1)).normalize();
}
Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 normal, Material* material)
	:m_v0{ p1 }, m_v1{ p2 }, m_v2{ p3 }, m_normal{ normal }, Object{ material } {
}


//point can be changed to vec3
Vec3 Triangle::calculate_normal() {

	return Vec3{
		(m_v1 - m_v0).cross(m_v2 - m_v0).normalize()
	};
}
//https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

bool Triangle::ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) {

	//Plane edges normal
	Vec3 edge1 = m_v1 - m_v0;
	Vec3 edge2 = m_v2 - m_v0;
	Vec3 ray_cross_e2 = ray.m_direction.cross(edge2);
	float det = edge1.dot(ray_cross_e2);

	//check if ray parallel to plane, meaning dot ptoduct 0
	if (det > -Constants::kEPSILON && det < Constants::kEPSILON)
		return false;

	float inv_det = 1.0 / det;
	Vec3 s = ray.m_origin - m_v0;
	float u = inv_det * s.dot(ray_cross_e2);

	if ((u<0 && std::abs(u)>Constants::kEPSILON) ||
		(u > 1 && std::abs(u - 1) > Constants::kEPSILON))
		return false;

	Vec3 s_cross_e1 = s.cross(edge1);
	float v = inv_det * ray.m_direction.dot(s_cross_e1);

	if ((v<0 && std::abs(v)>Constants::kEPSILON) ||
		(u + v > 1 && std::abs(u + v - 1) > Constants::kEPSILON))
		return false;

	//now we know ray intersects with the triangle
	float t = inv_det * edge2.dot(s_cross_e1);
	if (t < Constants::kEPSILON)
		return false;
	tmin = t;
	intersection = (ray.m_origin + ray.m_direction * t);
	normal = calculate_normal();
	return true;


}

Box Triangle::calculate_bb() {

	Vec3 min{};
	Vec3 max{};

	min.x=(std::min(std::min(m_v0.x, m_v1.x),m_v2.x) - Constants::kEPSILON);
	min.y=(std::min(std::min(m_v0.y, m_v1.y),m_v2.y) - Constants::kEPSILON);
	min.z=(std::min(std::min(m_v0.z, m_v1.z),m_v2.z) - Constants::kEPSILON);


	max.x=(std::max(std::max(m_v0.x, m_v1.x), m_v2.x) + Constants::kEPSILON);
	max.y=(std::max(std::max(m_v0.y, m_v1.y), m_v2.y) + Constants::kEPSILON);
	max.z=(std::max(std::max(m_v0.z, m_v1.z), m_v2.z) + Constants::kEPSILON);

	return Box{ min,max };

}

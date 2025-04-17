#include "Rectangle.h"
#include "..\Math\Constants.h"

Rectangle::Rectangle() :Object{} {}
Rectangle::Rectangle(Vec3 p, Vec3 shortEdge, Vec3 longEdge) :
	Object{}, m_origin{ p }, m_edge1{ shortEdge }, m_edge2{ longEdge }, m_normal{shortEdge.cross(longEdge).normalize()} {
}
Rectangle::Rectangle(Vec3 p, Vec3 shortEdge, Vec3 longEdge, Material* mat) :
	Object{mat}, m_origin{ p }, m_edge1{ shortEdge }, m_edge2{ longEdge }, m_normal{ shortEdge.cross(longEdge).normalize() } {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
	if (this == &other)
		return *this;
	m_sampler = other.m_sampler;
	m_origin = other.m_origin;
	m_edge1 = other.m_edge1;
	m_edge2 = other.m_edge2;
	m_normal = other.m_normal;
}

Vec3 Rectangle::get_sample() {
	double x = m_sampler.sample();
	double y = m_sampler.sample();

	return m_origin + m_edge1 * x + m_edge2 * y;
}
Vec3 Rectangle::get_normal(const Vec3& point) {

	return m_normal;
}
double Rectangle::get_pdf() {
	return 1 / m_edge1.length() * m_edge2.length();
}
Box Rectangle::calculate_bb() {
	//Corners={p0, p0+a, p0+b, p0+a+b}
	double min_x = std::min(m_origin.x, m_origin.x + m_edge1.x + m_edge2.x);
	double min_y = std::min(m_origin.y, m_origin.y + m_edge1.y + m_edge2.y);
	double min_z = std::min(m_origin.z, m_origin.z + m_edge1.z + m_edge2.z);

	double max_x = std::max(m_origin.x, m_origin.x + m_edge1.x + m_edge2.x);
	double max_y = std::max(m_origin.y, m_origin.y + m_edge1.y + m_edge2.y);
	double max_z = std::max(m_origin.z, m_origin.z + m_edge1.z + m_edge2.z);


	return Box{
		Vec3{min_x,min_y,min_z},Vec3{max_x,max_y,max_z}
	};
}
bool Rectangle::ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) {

	//find t
	float t = Vec3{ m_origin - ray.m_origin}.dot(m_normal) / (ray.m_direction.dot(m_normal));

	if (t <= Constants::kEPSILON) {
		return false;
	}

	//find intersection
	Vec3 p = ray.m_origin + t*ray.m_direction;

	//isInside?
	Vec3 d = p - m_origin;

	double ddota = d.dot(m_edge1);
	if (ddota < 0 || ddota > m_edge1.length() * m_edge1.length())
		return false;
	double ddotb = d.dot(m_edge2);
	if (ddotb < 0 || ddotb > m_edge2.length() * m_edge2.length())
		return false;

	tmin = t;
	intersection = d;//might also be p
	normal = m_normal;
	return true;
}

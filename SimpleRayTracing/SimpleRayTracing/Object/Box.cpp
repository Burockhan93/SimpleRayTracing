#include "Box.h"

Box::Box(const Vec3& p1, const Vec3& p2) : m_p1{ p1 }, m_p2{ p2 } {}
Box& Box::operator=(const Box& other) {
	if (this == &other)
		return *this;
	m_p1 = other.m_p1;
	m_p2 = other.m_p2;
	return *this;
}

bool Box::inside(const Vec3& p) {

	return (p.x>= m_p1.x && p.x<=m_p2.x)
		&& (p.y>=m_p1.y && p.y<=m_p2.y)
		&& (p.z >= m_p1.z && p.z <= m_p2.z);
		
}
//https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
bool Box::hit(const Ray& ray, double& t) {
	using namespace std;
	Vec3 dirfrac{};

	dirfrac.x=(1.0f / ray.m_direction.x);
	dirfrac.y=(1.0f / ray.m_direction.y);
	dirfrac.z=(1.0f / ray.m_direction.z);
	// p1 is the corner of AABB with minimal coordinates - left bottom, p2 is maximal corner


	float t1 = (m_p1.x - ray.m_origin.x) * dirfrac.x;
	float t2 = (m_p2.x - ray.m_origin.x) * dirfrac.x;
	float t3 = (m_p1.y - ray.m_origin.y) * dirfrac.y;
	float t4 = (m_p2.y - ray.m_origin.y) * dirfrac.y;
	float t5 = (m_p1.z - ray.m_origin.z) * dirfrac.z;
	float t6 = (m_p2.z - ray.m_origin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
}
Vec3* Box::set_vertices(Vec3 v[8]) {
	v[0] = m_p1;
	v[1] = Vec3(m_p2.x, m_p1.y, m_p1.z);
	v[2] = Vec3(m_p2.x, m_p2.y, m_p1.z);
	v[3] = Vec3(m_p1.x, m_p2.y, m_p1.z);

	v[4] = m_p2;
	v[5] = Vec3(m_p1.x, m_p2.y, m_p2.z);
	v[6] = Vec3(m_p1.x, m_p1.y, m_p2.z);
	v[7] = Vec3(m_p2.x, m_p2.y, m_p2.z);

	return v;
}


#pragma once
#include "..\Math\Ray.h"
#include "..\Math\Vec3.h"

class Box {
private:
public:
	//members
	Vec3 m_p1{}, m_p2{};//p1 left bottom, p2 right top

	//constructor

	Box() = default;
	Box(const Vec3& p1, const Vec3& p2);
	~Box() = default;

	//coppy asignment
	Box& operator=(const Box& other);

	//methods

	bool inside(const Vec3& point);
	bool hit(const Ray& ray, double& t);
	Vec3* set_vertices(Vec3 p[8]);
};

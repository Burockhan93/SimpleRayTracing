#pragma once
#include "Object.h"
#include "Box.h"
#include "..\Math\Vec3.h"
#include "..\Math\Ray.h"

class Triangle: public Object {
protected:
	Vec3 m_v0{}, m_v1{}, m_v2{};
	Vec3 m_normal{};
public:
	//constructors
	Triangle() = default;
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3,Material* material);
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3,Vec3 normal, Material* material);
	~Triangle() = default;
	//methods
	Vec3 calculate_normal();
	Box calculate_bb() override;
	bool ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) override;

};
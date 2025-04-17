#pragma once
#include "Object.h"


class Plane : public Object {

private:
	Vec3 m_normal{};
	Vec3 m_pos{};
public:
	//constructors

	Plane();
	Plane(Vec3 pos, Vec3 normal, Material* material);
	Plane(Vec3 pos, Vec3 normal);
	Plane(const Plane& other);

	//methods

	Box calculate_bb() override;
	bool ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) override;

};
#pragma once
#include "Object.h"
#include "..\Utils\Sampler.h"

class Rectangle: public Object {
private:
	Sampler m_sampler{};
	Vec3 m_origin{};
	Vec3 m_edge1{};
	Vec3 m_edge2{};
public:
	//membrs
	Vec3 m_normal{};
	//constructors

	Rectangle();
	Rectangle(Vec3 p, Vec3 shortEdge, Vec3 longEdge);
	Rectangle(Vec3 p, Vec3 shortEdge, Vec3 longEdge, Material* mat);
	~Rectangle() = default;

	//copy asignment
	Rectangle& operator=(const Rectangle& other);

	//methods
	Vec3 get_sample() override;
	Vec3 get_normal(const Vec3& point) override;
	double get_pdf() override;
	Box calculate_bb() override;
	bool ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) override;

};

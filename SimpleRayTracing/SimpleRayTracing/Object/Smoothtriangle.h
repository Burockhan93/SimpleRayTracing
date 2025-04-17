#pragma once

#include "Triangle.h"

class SmoothTriangle :public Triangle {
public:
	SmoothTriangle();
	SmoothTriangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 n0, Vec3 n1, Vec3 n2, Material* mat);
	SmoothTriangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 n0, Vec3 n1, Vec3 n2);
	Vec3 calculate_normal_smooth(double gamma, double beta);
private:
	Vec3 m_n0{}, m_n1{}, m_n2{};

};
#include "Smoothtriangle.h"

SmoothTriangle::SmoothTriangle():Triangle(){}
SmoothTriangle::SmoothTriangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 n0, Vec3 n1, Vec3 n2, Material* mat) :Triangle{ v0,v1,v2,mat }, m_n0{ n0 },m_n1{n1},m_n2{n2}{}
SmoothTriangle::SmoothTriangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 n0, Vec3 n1, Vec3 n2) :Triangle{ v0,v1,v2 }, m_n0{ n0 },m_n1{n1},m_n2{n2}{}
Vec3 SmoothTriangle::calculate_normal_smooth(double gamma, double beta) {
	return Vec3{ ((1 - beta - gamma) * m_n0) + (m_n1 * beta) + (m_n2 * gamma) }.normalize();
}

#include "sphere.h"

Sphere::Sphere(): Object{}{}
Sphere::Sphere(Vec3 origin, double radius, Material* material):
	Object{ material }, m_radius{ radius }, m_center{origin} {}

Sphere::Sphere(Vec3 origin, double radius) :
	Object{}, m_radius{ radius }, m_center{ origin } {}
Sphere::Sphere(const Sphere& sphere) :
	Object{ sphere.get_shader() }, m_center{ sphere.m_center }, m_radius{sphere.m_radius} {}


Vec3 Sphere::get_sample() {
	double r1 = m_sampler.sample(), r2 = m_sampler.sample();

	double theta = 2 * Constants::PI * r1;
	double phi = acos(1 - 2 * r2);
	double x = m_radius * sin(phi) * cos(theta);
	double y = m_radius * sin(phi) * sin(theta);
	double z = m_radius * cos(phi);

	return Vec3{x, y, z} + m_center;
}
Vec3 Sphere::get_normal(const Vec3& point){

	return (point - m_center).normalize();
}
Box Sphere::calculate_bb() {
	Vec3 min{ m_center.x - m_radius,m_center.y - m_radius ,m_center.z - m_radius };
	Vec3 max{ m_center.x + m_radius,m_center.y + m_radius ,m_center.z + m_radius };
	return Box{ min,max };
}
double Sphere::get_pdf() {
	return 1 / (4 * Constants::PI * m_radius * m_radius);
}
//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
bool Sphere::ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) {
	float t0, t1; // Solutions for t if the ray intersects the sphere


	// Analytic solution
	Vec3 L = ray.m_origin - m_center;
	float a = ray.m_direction.dot(ray.m_direction);
	float b = 2 * ray.m_direction.dot(L);
	float c = L.dot(L) - m_radius * m_radius;
	if (!solve_quadratic(a, b, c, t0, t1)) return false;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < Constants::kEPSILON) {
		t0 = t1; // If t0 is negative, let's use t1 instead.
		if (t0 < 0) return false; // Both t0 and t1 are negative.
	}

	tmin = t0;
	intersection = ray.m_origin + (ray.m_direction * tmin);
	normal = (intersection - m_center).normalize();

	return true;
}
bool Sphere::solve_quadratic(const float& a, const float& b, const float& c,float& x0, float& x1) {
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}

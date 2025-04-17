#include "Ray.h"

Ray::Ray(Vec3 origin, Vec3 direction) : m_origin{ origin }, m_direction{ direction } {}

Ray::Ray(const Ray& ray) : m_origin{ ray.m_origin }, m_direction{ ray.m_direction } {}

Ray& Ray::operator=(const Ray& ray) {
	if (this == &ray) 
		return *this;
	m_origin = ray.m_origin;
	m_direction = m_direction;
}

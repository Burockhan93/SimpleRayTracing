#include <cassert>
#include "Camera.h"
#include "..\Math\Constants.h"
#include <random>

Camera::Camera(Vec3 lookfrom, Vec3 lookto, double fovy)
	: m_eye{ lookfrom }, m_lookat{ lookto }, m_fovy{ fovy }
	, m_aspect{ static_cast<double>(width) / static_cast<double>(height) }
	, m_direction{ (lookto - lookfrom).normalize() }
	, m_up{ 0,1,0 } {
		//https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix.html#:~:text=The%20value%20of%20the%20field,subtended%20by%20the%20viewing%20cone.
	double tetha = fovy * Constants::PI/180;
	double view_width = tan(tetha / 2) * m_distance;
	double view_height = view_width / m_aspect;

	//full view
	m_horizontal = view_width * 2;
	m_vertical = view_height * 2;

	//view center 
	Vec3 center = m_eye + (m_direction * m_distance);
	//basis vectors
	m_x = m_direction.neg();//negate the direction
	m_z = (m_up.cross(m_x)).normalize();//m_z is ortagonal to m_x and up
	m_y = m_x.cross(m_z); //m_y ortagonal to m_z and m_x
	
	//upper corner on full view
	m_upper_corner = center + (m_z.neg() * view_width) + (m_y * view_height);

}
Camera::Camera(const Camera& other) {
	m_eye = other.m_eye;
	m_up = other.m_up;
	m_lookat = other.m_lookat;
	m_direction = other.m_direction;
	m_fovy = other.m_fovy;
	m_aspect = other.m_aspect;
	m_upper_corner = other.m_upper_corner;
	m_horizontal = other.m_horizontal;
	m_vertical = other.m_vertical;
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
}
Camera& Camera::operator=(const Camera& other) {
	if (this == &other)
		return *this;
	m_eye = other.m_eye;
	m_up = other.m_up;
	m_lookat = other.m_lookat;
	m_direction = other.m_direction;
	m_fovy = other.m_fovy;
	m_aspect = other.m_aspect;
	m_upper_corner = other.m_upper_corner;
	m_horizontal = other.m_horizontal;
	m_vertical = other.m_vertical;
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
	return *this;
}
Ray Camera::construct_ray(int i, int j) {
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<> dis(0.0, 1.0);


	double x = dis(gen);
	double y = dis(gen);
	//camera plane
	return Ray(m_eye, (m_upper_corner + (m_z * (j + x) * (m_horizontal / double(width))) + (m_y.neg() * (i + y) * (m_vertical / double(height)))) - m_eye);
}
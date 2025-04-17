#pragma once
#include "..\Math\Vec3.h"
#include "..\Math\Constants.h"

class Hit {
private:

public:
	//members
	double m_distance{INFINITY};
	Vec3 m_normal{};
	Vec3 m_direction{};
	Vec3 m_hitPoint{};
	Hit() = default;
	Hit(double distance, Vec3 normal, Vec3 direction, Vec3 hit)
		:	m_distance{distance},m_normal{normal},m_direction{direction},m_hitPoint{hit}{ }

	~Hit()=default;

	friend class RayTracer;
	friend class EnvironmentTracer;
	

};
#pragma once

#include "..\Math\Vec3.h"
#include "..\Utils\Hit.h"
#include "..\Builder\World.h"
#include "..\Math\Ray.h"

class Light {
protected:
	Vec3 m_color{};
	double m_intensity{};
public:
	//constructors
	Light() = default;
	Light(Vec3 color, double intensity) :m_color{ color }, m_intensity{ intensity } {}
	//coppy assignment
	Light& operator=(const Light& other) {
		if (this == &other)
			return *this;
		m_color = other.m_color;
		m_intensity = other.m_intensity;

		return *this;
	}

	//virtual methods

	Vec3 virtual get_direction(const Hit& hit) = 0;
	Vec3 virtual get_intensity(const Hit& hit, World& world) = 0;
	bool virtual shadow_hit(const Ray& ray, World& world) = 0;
};
#pragma once
#include "..\Builder\World.h"
#include "..\Math\Vec3.h"
#include "..\Utils\Hit.h"

class Material {
public:
	Material() = default;
	Material(const Material& other){}
	~Material() = default;

	Material& operator=(const Material& other) {
		if (this == &other)
			return *this;
		return *this;
	}

	virtual Vec3 direct_shade(Hit& hit, World& world, int depth) { return Vec3{}; }
	virtual Vec3 indirect_shade(Hit& hit, World& world, int depth) { return Vec3{}; }
};

#pragma once

#include "Object.h"

class Composite: public Object {
public:
	std::vector<Object*> objects{};
public:
	//construcctor

	Composite() = default;
	Composite(Material* shader);
	~Composite()=default;

	//methods

	Box virtual calculate_bb() override;
	bool virtual ray_intersects(Ray const& ray, Vec3& intersection, double& tmin, Vec3& normal) override;
	void virtual add_object(Object* object) override;
	 
};
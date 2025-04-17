#pragma once
#include "..\Builder\World.h"
class RayTracer {
public:
	//constructors
	RayTracer() = default;
	~RayTracer() = default;

	//methods
	Vec3 trace_ray(const Ray& ray, World& world, int depth);
};
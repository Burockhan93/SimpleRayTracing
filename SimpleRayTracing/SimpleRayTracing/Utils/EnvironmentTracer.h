#pragma once
#include "..\Material\Material.h"
#include "..\Builder\World.h"
#include "..\Math\Ray.h"
#include "..\Object\Object.h"

class EnvironmentTracer {
public:
	//constructors
	EnvironmentTracer()=default;
	~EnvironmentTracer()=default;

	Vec3 trace_ray(const Ray& ray, World& world, int depth);


};
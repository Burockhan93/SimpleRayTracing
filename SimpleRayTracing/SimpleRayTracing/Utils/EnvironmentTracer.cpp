#include "EnvironmentTracer.h"

Vec3 EnvironmentTracer::trace_ray(const Ray& ray, World& world, int depth) {
	if (depth > Constants::BOUNCE)
		return Vec3{};

	Vec3 color {};
	double t = INFINITY;
	Hit hit{};
	hit.m_direction=ray.m_direction;
	hit.m_distance = INFINITY;
	Object* closest = nullptr;
	Vec3 intersection{};
	Vec3 normal{};
	bool isHit{ false };
	for (Object* obj : world.m_objects) {
		if (obj->ray_intersects(ray, intersection, t, normal)) {
			if (t < hit.m_distance) {
				hit.m_hitPoint = intersection;
				hit.m_normal = normal;
				hit.m_distance = t;
				closest = obj;
				isHit = true;
			}
		}
	}

	return 
		isHit ? closest->get_shader()->indirect_shade(hit, world, depth) : Vec3{ 1 };

	
}
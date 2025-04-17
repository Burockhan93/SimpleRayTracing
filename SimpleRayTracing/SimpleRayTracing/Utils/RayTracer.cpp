#include "..\Material\Material.h"
#include "RayTracer.h"
#include "..\Math\Constants.h"
#include "Hit.h"

Vec3 RayTracer::trace_ray(const Ray& ray, World& world, int depth) {
	if (depth > Constants::BOUNCE)
		return Vec3{};

    double t = INFINITY;
    Hit hit;
    hit.m_direction=(ray.m_direction);

    Object* closest = nullptr;
    Vec3 intersection;
    Vec3 normal;

    bool isHit = false;

    for (Object* obj : world.m_objects) {
        if (obj->ray_intersects(ray, intersection, t, normal)) {
            if (t < hit.m_distance) {
                //we found a closer object.
                hit.m_hitPoint = intersection;
                hit.m_normal = normal;
                hit.m_distance = t;
                closest = obj;
                isHit = true;
            }
        }
    }
    if (isHit) {
        Vec3 color = closest->get_shader()->indirect_shade(hit, world, depth);
        return color;
    }
    else {
        //no hit environment color.
        return Vec3{ 0 };
    }
    
}
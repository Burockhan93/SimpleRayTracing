#include "Instance.h"

Instance::Instance() :Object{}, m_transform{}, m_object{} {}
Instance::Instance(Object* object, Material* material) :Object{ material }, m_object{ object }, m_transform{} {}
Instance::~Instance() { delete m_object; }

void Instance::translate(const Vec3& vec) {
	m_transform.translate(vec);
}
void Instance::scale(const Vec3& vec) {
	m_transform.scale(vec);
}
void Instance::rotate(double x, double y, double z) {
	m_transform.rotate(x, y, z);
}

bool Instance::ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) {
	//convert to local
	Ray inv_ray{ ray };
	inv_ray.m_direction=(m_transform.global_to_local(ray.m_direction));
	inv_ray.m_origin=(m_transform.global_to_local(ray.m_origin));

	if (m_object->ray_intersects(inv_ray, intersection, tmin, normal)) {
		intersection = m_transform.local_to_global(intersection);
		normal = m_transform.local_to_global(normal).normalize();
		return true;
	}
	return false;
}
Box Instance::calculate_bb() {
	double min_x = INFINITY, min_y = INFINITY, min_z = INFINITY;
	double max_x = -INFINITY, max_y = -INFINITY, max_z = -INFINITY;

	Box b = m_object->calculate_bb();
	Vec3 vertices[8];
	b.set_vertices(vertices);

	//transform tzhe bb into local ccordinates
	for (size_t i = 0; i < 8; i++)
	{
		vertices[i] = m_transform.global_to_local(vertices[i]);
	}
	// we need to find min max yet again in local coordinates 
	for (size_t i = 0; i < 8; i++)
	{
		if (vertices[i].x < min_x)
			min_x = vertices[i].x;
		if (vertices[i].y < min_y)
			min_y = vertices[i].y;
		if (vertices[i].z < min_z)
			min_z = vertices[i].z;

		if (vertices[i].x > max_x)
			max_x = vertices[i].x;
		if (vertices[i].y > max_y)
			max_y = vertices[i].y;
		if (vertices[i].z > max_z)
			max_z = vertices[i].z;
	}


	return Box{
		Vec3(min_x,min_y,min_z),Vec3(max_x,max_y,max_z)
	};
}
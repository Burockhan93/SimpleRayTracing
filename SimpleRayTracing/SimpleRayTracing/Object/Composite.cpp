#include "Composite.h"
#include "..\Math\Constants.h"

Composite::Composite(Material* shader) :Object{ shader } {}

//bb is the compoisition of every element
Box Composite::calculate_bb() {
	double min_x = INFINITY, min_y = INFINITY, min_z = INFINITY;
	double max_x = -INFINITY, max_y = -INFINITY, max_z = -INFINITY;

	for (Object* obj : objects) {

		Box b = obj->calculate_bb();
		Vec3 vertices[8];
		b.set_vertices(vertices);

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

	}
	return Box{
		Vec3(min_x,min_y,min_z),Vec3(max_x,max_y,max_z)
	};

}
bool Composite::ray_intersects(Ray const& ray, Vec3& intersection, double& tmin, Vec3& normal) {

	bool hit{};
	Vec3 n{};
	Vec3 intersect{};
	double t{};
	double tmax = INFINITY;
	for (Object* obj : objects) {
		if (obj->ray_intersects(ray, intersect, t, n)) {
			if (tmax > t) {
				tmin = t;
				intersection = intersect;
				normal = n;
				set_shader(obj->get_shader());
				hit = true;

			}
		}
	}
	return hit;

}
void Composite::add_object(Object* object) {
	objects.push_back(object);
}
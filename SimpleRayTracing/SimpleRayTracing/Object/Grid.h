#pragma once
#include "Object.h"
#include "Composite.h"
#include "..\ObjectHandler\Mesh.h"

class Grid : public Object {
private:
public:
	//constructors

	Grid();
	Grid(const Mesh& mesh, Material* mat);
	~Grid();
	//methods
	bool ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal)override;
	Box calculate_bb();
	void add_object(Object* object);
	void construct_cells();

private:
	Box m_boundingbox{};
	int m_x{}, m_y{}, m_z{};
	int m_density{ 5 };
	std::vector<Object*> m_objects;
	std::vector<Composite*> m_cells;
};
#include "Grid.h"
#include "..\Math\Constants.h"
#include "..\Math\MathUtils.h"
#include "..\Object\Triangle.h"
#include "..\Object\Smoothtriangle.h"


Grid::Grid() :Object{} {}
Grid::~Grid() {
	Object::~Object();
	m_objects.clear();
	m_cells.clear();
	m_boundingbox.~Box();
}
Grid::Grid(const Mesh& mesh, Material* mat) :Object() {
	for (size_t i = 0; i < mesh.m_indices.size(); i += 3)
	{
		Triangle* triangle;
		if (mesh.m_smoothShading) {
			triangle = new SmoothTriangle(
				Vec3{ mesh.m_positions[mesh.m_indices[i]] },
				Vec3{ mesh.m_positions[mesh.m_indices[i + 1]] },
				Vec3{ mesh.m_positions[mesh.m_indices[i + 2]] },
				Vec3{ mesh.m_normals[mesh.m_indices[i]] },
				Vec3{ mesh.m_normals[mesh.m_indices[i + 1]] },
				Vec3{ mesh.m_normals[mesh.m_indices[i + 2]] },
				mat
			);
		}
		else {
			triangle = new Triangle(
				Vec3{ mesh.m_positions[mesh.m_indices[i]] },
				Vec3{ mesh.m_positions[mesh.m_indices[i + 1]] },
				Vec3{ mesh.m_positions[mesh.m_indices[i + 2]] },
				mat
			);
		}

		add_object(triangle);
	}
	construct_cells();
}
bool Grid::ray_intersects(const Ray& ray, Vec3& intersection, double& tmin, Vec3& normal) {
    double ox = ray.m_origin.x;
    double oy = ray.m_origin.y;
    double oz = ray.m_origin.z;
    double dx = ray.m_direction.x;
    double dy = ray.m_direction.y;
    double dz = ray.m_direction.z;

    double x0 = m_boundingbox.m_p1.x;
    double y0 = m_boundingbox.m_p1.y;
    double z0 = m_boundingbox.m_p1.z;
    double x1 = m_boundingbox.m_p2.x;
    double y1 = m_boundingbox.m_p2.y;
    double z1 = m_boundingbox.m_p2.z;

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;


    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }

    double t0, t1;

    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;

    if (tz_min > t0)
        t0 = tz_min;

    if (tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;

    if (tz_max < t1)
        t1 = tz_max;

    if (t0 > t1)
        return(false);


    // initial cell coordinates

    int ix, iy, iz;

    if (m_boundingbox.inside(ray.m_origin)) {              // does the ray start inside the grid?
        ix = clamp((ox - x0) * m_x / (x1 - x0), 0, m_x - 1);
        iy = clamp((oy - y0) * m_y / (y1 - y0), 0, m_y - 1);
        iz = clamp((oz - z0) * m_z / (z1 - z0), 0, m_z - 1);
    }
    else {
        Vec3 p = ray.m_origin + t0 * ray.m_direction;  // initial hit point with grid's bounding box
        ix = clamp((p.x - x0) * m_x / (x1 - x0), 0, m_x - 1);
        iy = clamp((p.y - y0) * m_y / (y1 - y0), 0, m_y - 1);
        iz = clamp((p.z - z0) * m_z / (z1 - z0), 0, m_z - 1);
    }

    // ray parameter increments per cell in the x, y, and z directions

    double dtx = (tx_max - tx_min) / m_x;
    double dty = (ty_max - ty_min) / m_y;
    double dtz = (tz_max - tz_min) / m_z;

    double     tx_next, ty_next, tz_next;
    int     ix_step, iy_step, iz_step;
    int     ix_stop, iy_stop, iz_stop;

    if (dx > 0) {
        tx_next = tx_min + (ix + 1) * dtx;
        ix_step = +1;
        ix_stop = m_x;
    }
    else {
        tx_next = tx_min + (m_x - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }

    if (dx == 0.0) {
        tx_next = INFINITY;
        ix_step = -1;
        ix_stop = -1;
    }


    if (dy > 0) {
        ty_next = ty_min + (iy + 1) * dty;
        iy_step = +1;
        iy_stop = m_y;
    }
    else {
        ty_next = ty_min + (m_y - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }

    if (dy == 0.0) {
        ty_next = INFINITY;
        iy_step = -1;
        iy_stop = -1;
    }

    if (dz > 0) {
        tz_next = tz_min + (iz + 1) * dtz;
        iz_step = +1;
        iz_stop = m_z;
    }
    else {
        tz_next = tz_min + (m_z - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }

    if (dz == 0.0) {
        tz_next = INFINITY;
        iz_step = -1;
        iz_stop = -1;
    }


    // traverse the grid

    while (true) {
        Object* object_ptr = m_cells[ix + m_x * iy + m_x * m_y * iz];

        if (tx_next < ty_next && tx_next < tz_next) {
            if (object_ptr && object_ptr->ray_intersects(ray, intersection, tmin, normal) && object_ptr->calculate_bb().inside(intersection)) {
                set_shader(object_ptr->get_shader());
                return (true);
            }

            tx_next += dtx;
            ix += ix_step;

            if (ix == ix_stop)
                return (false);
        }
        else {
            if (ty_next < tz_next) {
                if (object_ptr && object_ptr->ray_intersects(ray, intersection, tmin, normal) && object_ptr->calculate_bb().inside(intersection)) {
                    set_shader(object_ptr->get_shader());
                    return (true);
                }

                ty_next += dty;
                iy += iy_step;

                if (iy == iy_stop)
                    return (false);
            }
            else {
                if (object_ptr && object_ptr->ray_intersects(ray, intersection, tmin, normal) && object_ptr->calculate_bb().inside(intersection)) {
                    set_shader(object_ptr->get_shader());
                    return (true);
                }

                tz_next += dtz;
                iz += iz_step;

                if (iz == iz_stop)
                    return (false);
            }
        }
    }
}
void Grid::add_object(Object* object) {
    m_objects.push_back(object);
}
void Grid::construct_cells() {
    
    double min_x = INFINITY, min_y = INFINITY, min_z = INFINITY;
    double max_x = -INFINITY, max_y = -INFINITY, max_z = -INFINITY;
    for (Object* object : m_objects) {
        Box bboxObject = object->calculate_bb();
//vertices of bb
        Vec3 v[8];
        bboxObject.set_vertices(v);
        for (int i = 0; i < 8; i++) {
            if (v[i].x < min_x)
                min_x = v[i].x;
            if (v[i].y < min_y)
                min_y = v[i].y;
            if (v[i].z < min_z)
                min_z = v[i].z;
            if (v[i].x > max_x)
                max_x = v[i].x;
            if (v[i].y > max_y)
                max_y = v[i].y;
            if (v[i].z > max_z)
                max_z = v[i].z;
        }
    }

    Vec3 gridMin = Vec3{ min_x - Constants::kEPSILON, min_y - Constants::kEPSILON, min_z - Constants::kEPSILON };
    Vec3 gridMax = Vec3{ max_x + Constants::kEPSILON, max_y + Constants::kEPSILON, max_z + Constants::kEPSILON };

    m_boundingbox = Box{ gridMin, gridMax };

    //find the size of the bounding box and volume of the bounding box.
    double Sx = max_x - min_x, Sy = max_y - min_y, Sz = max_z - min_z;

    int N = m_objects.size();
    double V = Sx * Sy * Sz;

    // Mi = Si * pow( (density * N)/V, 0,333333)


    m_x = Sx * pow((m_density * N) / V, 0.33333) + 1;
    m_y = Sy * pow((m_density * N) / V, 0.33333) + 1;
    m_z = Sz * pow((m_density * N) / V, 0.33333) + 1;


    int num_cels = m_x * m_y * m_z;

    //create array of the number of cells.
    for (int i = 0; i < num_cels; i++)
        m_cells.push_back(nullptr);

    for (Object* obj : m_objects) {
        //find cells that overlap with bounding box.
        Box objBox = obj->calculate_bb();

        Vec3 min_distance = objBox.m_p1 - gridMin;
        Vec3 max_distance = objBox.m_p2 - gridMin;

        //calculate index.
        int ix_min = clamp((min_distance.x / Sx) * m_x, 0, m_x - 1);
        int iy_min = clamp((min_distance.y / Sy) * m_y, 0, m_y - 1);
        int iz_min = clamp((min_distance.z / Sz) * m_z, 0, m_z - 1);

        int ix_max = clamp((max_distance.x / Sx) * m_x, 0, m_x - 1);
        int iy_max = clamp((max_distance.y / Sy) * m_y, 0, m_y - 1);
        int iz_max = clamp((max_distance.z / Sz) * m_z, 0, m_z - 1);

        for (int iz = iz_min; iz <= iz_max; ++iz) {
            for (int iy = iy_min; iy <= iy_max; ++iy) {
                for (int ix = ix_min; ix <= ix_max; ++ix) {
                    int i = ix + m_x * iy + m_x*m_y * iz;

                    // Ensure index is within bounds
                    if (i < 0 || i >= static_cast<int>(m_cells.size())) {
                        std::cerr << "Error: Index " << i << " out of bounds (0-" << m_cells.size() - 1 << ")\n";
                        continue;  // Skip invalid indices
                    }

                    if (m_cells[i]) {
                        m_cells[i]->add_object(obj);
                    }
                    else {
                        Composite* composite = new Composite;
                        composite->add_object(obj);
                        m_cells[i] = composite;
                    }
                }
            }
        }

    }

}
Box Grid::calculate_bb() {
    return m_boundingbox;
}

#include "Mesh.h"

Mesh::Mesh(bool smoothShading, const std::string& name,
	const std::vector<Vec3>& positions,
	const std::vector<Vec3>& normals,
	const std::vector<Vec2>& UVs,
	const std::vector<unsigned int>& indices):
	m_smoothShading{smoothShading},
	m_name{name},
	m_positions{positions},
	m_normals{normals},
	m_UVs{UVs},
	m_indices{indices}{}
Mesh::Mesh(bool smoothShading, const std::string& name,
	const std::vector<Vec3>& positions,
	const std::vector<Vec3>& normals,
	const std::vector<unsigned int>& indices) :
	m_smoothShading{ smoothShading },
	m_name{ name },
	m_positions{ positions },
	m_normals{ normals },
	m_indices{ indices } {
}
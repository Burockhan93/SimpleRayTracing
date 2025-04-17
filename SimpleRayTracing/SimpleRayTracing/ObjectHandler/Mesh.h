#pragma once
#include <string>
#include <vector>
#include "..\Math\Vec3.h"
#include "..\Math\Vec2.h"
class Mesh {
public:
	bool m_smoothShading{};
	std::string m_name{};
	std::vector<Vec3> m_positions{};
	std::vector<Vec3> m_normals{};
	std::vector<Vec2> m_UVs{};
	std::vector<unsigned int> m_indices{};
public:
	//constructors
	Mesh()=default;
	Mesh(bool smoothShading, const std::string& name,
		const std::vector<Vec3>& positions,
		const std::vector<Vec3>& normals,
		const std::vector<Vec2>& UVs,
		const std::vector<unsigned int>& indices);
	Mesh(bool smoothShading, const std::string& name,
		const std::vector<Vec3>& positions,
		const std::vector<Vec3>& normals,
		const std::vector<unsigned int>& indices);
	~Mesh()=default;
};
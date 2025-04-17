#pragma once

#include <iostream>
#include "Mesh.h"
#include "Vertex.h"

class OBJHandler {
public:
	Mesh m_mesh;
	std::vector<Mesh> m_meshes{};
	const std::string m_extension{ ".obj" };
	const std::string m_vertex{ "v "};
	const std::string m_face{ 'f' };
	const std::string m_normals{ "vn " };
	const std::string m_faceseperator{ "/" };
	//bool constructors
	OBJHandler()=default;
	~OBJHandler() = default;

	//methods
	bool load_mesh(std::string filePath);
	void splitFaceLines(std::string str);
	Mesh& get_mesh();
	std::vector<Mesh>& get_meshes();

};

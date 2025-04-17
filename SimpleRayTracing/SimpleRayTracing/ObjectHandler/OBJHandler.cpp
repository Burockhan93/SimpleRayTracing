#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include "OBJHandler.h"

Mesh& OBJHandler::get_mesh() {
	return m_mesh;
}std::vector<Mesh>& OBJHandler::get_meshes() {
	return m_meshes;
}


bool OBJHandler::load_mesh(std::string filePath) {
    // Check file extension
    if (filePath.substr(filePath.size() - 4, 4) != m_extension) {
        std::cout << "No .obj file found at given file location: " << filePath << std::endl;
        return false;
    }

    std::ifstream file(filePath, std::ifstream::in);
    if (!file.is_open()) {
        std::cout << "File was not opened!" << std::endl;
        return false;
    }

    std::cout << "Reading file from: " << filePath << '\n';

    bool smoothShading{ false };
    std::string name{};
    std::vector<Vertex> vertices{};
    std::vector<Vec3> positions{};
    std::vector<Vec3> normals{};
    std::vector<unsigned int> vertex_indices{};
    std::vector<Mesh> meshes{};
    std::string line{};
    int pos_offset{};
    int norm_offset{};

    try {
        while (std::getline(file, line)) {

            //encounter new mesh
            if (line.front() == 'o') {

                //vertices not empty means this is not the first mesh in the file
                if (!vertices.empty()) {
                    pos_offset += positions.size();
                    norm_offset += normals.size();
                    positions.clear();
                    normals.clear();
                    for (const Vertex& v : vertices) {
                        positions.push_back(v.Position);
                        normals.push_back(v.Normal);
                    }

                    meshes.emplace_back(smoothShading, name, positions, normals, vertex_indices);
                    positions.clear();
                    normals.clear();
                    vertices.clear();
                    vertex_indices.clear();
                }

                //get the name 
                line.erase(0, 2);
                name = line;
            }
            else if (line.front() == 'v') {
                if (line[1] == ' ') {
                    line.erase(0, 2);
                    std::istringstream iss(line);
                    float x, y, z;
                    iss >> x >> y >> z;
                    positions.emplace_back(x, y, z);
                }
                else if (line[1] == 'n') {
                    line.erase(0, 3);
                    std::istringstream iss(line);
                    float x, y, z;
                    iss >> x >> y >> z;
                    normals.emplace_back(x, y, z);
                }
            }
            else if (line.front() == 'f') {
                line.erase(0, 2);
                std::istringstream iss(line);
                std::string vertex_one, vertex_two, vertex_three, vertex_four;
                iss >> vertex_one >> vertex_two >> vertex_three>>vertex_four;

                auto parseVertex = [&](const std::string& v) -> Vertex {
                    size_t first_slash = v.find('/');
                   

                    int pos_index = (std::stoi(v.substr(0, first_slash)) - 1)-pos_offset;
                     if (v.at(first_slash + 1) == '/')
                    {
                        first_slash += 1;
                    }
                    else {
                       size_t i = first_slash+1;
                        while (v.at(i)!='/')
                        {
                            i++;
                        }
                        first_slash = i;
                    }
                    int norm_index = (std::stoi(v.substr(first_slash + 1)) - 1) - norm_offset;
                    return Vertex{ positions[pos_index], {0, 0}, normals[norm_index] };
                    };

                vertices.push_back(parseVertex(vertex_one));
                vertices.push_back(parseVertex(vertex_two));
                vertices.push_back(parseVertex(vertex_three));

                unsigned int index = vertices.size() - 3;
                vertex_indices.push_back(index);
                vertex_indices.push_back(index + 1);
                vertex_indices.push_back(index + 2);

                if (!vertex_four.empty()) {
                    vertices.push_back(parseVertex(vertex_four));

                    // Indices for second triangle (v1, v3, v4)
                    vertex_indices.push_back(index);
                    vertex_indices.push_back(index + 2);
                    vertex_indices.push_back(vertices.size() - 1);
                }

            }
        }

      
        if (!vertices.empty()) {

            positions.clear();
            normals.clear();

            for (const Vertex& v : vertices) {
                positions.push_back(v.Position);
                normals.push_back(v.Normal);
            }

            meshes.emplace_back(smoothShading, name, positions, normals, vertex_indices);
            positions.clear();
            normals.clear();
            vertices.clear();
            vertex_indices.clear();
        }
        std::cout << "mesh size: " << meshes.size() << std::endl;
        file.close();

        //multiple
        if (meshes.size()>1) {
            m_meshes=meshes;
        }
        else {
            m_mesh = meshes.front();;
        }

        return true;
    }
    catch (std::exception& e) {
        std::cout << "Error occurred during mesh creation phase: " << e.what() << std::endl;
        return false;
    }
}


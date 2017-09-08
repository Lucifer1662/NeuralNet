#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "glm.hpp"
using std::string;

using glm::vec2;
using glm::vec3;
using std::vector;

class Mesh {
public:
	vector<vec3> vertices;
	vector<size_t> indices;
	vector<vec2> uvs;
	string name;

	Mesh() {};

	Mesh(vec3* vertices, size_t vertSize, size_t* indices, size_t indexSize) {
		this->vertices = std::vector<vec3>(vertices, vertices + vertSize);
		this->indices = std::vector<size_t>(indices, indices + indexSize);
	}
};
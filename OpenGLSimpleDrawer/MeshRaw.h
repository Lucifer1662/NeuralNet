#pragma once
#include <vector>
#include <iostream>
#include "vec3ui.h"
#include "Mesh.h"

using std::vector;

class MeshRaw {
public:
	vector<vec3ui> atribCounts;
	vector<float> vertices;
	vector<size_t> indices;
	string name;

	MeshRaw(float* vertices, size_t vertSize, size_t* indices, size_t indexSize, vec3ui* atribCounts, size_t atribCount);
	MeshRaw(vector<float> vertices, vector<size_t> indices, vector<vec3ui> atribCounts);
	MeshRaw(Mesh mesh, vector<vec3ui> atribCounts);
	MeshRaw(Mesh mesh, vec3ui* atribCounts, size_t atribCount);
	MeshRaw(Mesh mesh);
	MeshRaw();
	void DestroyMesh();
};
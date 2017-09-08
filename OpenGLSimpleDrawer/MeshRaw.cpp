#pragma once
#include <vector>
#include <iostream>
#include "vec3ui.h"
#include "Mesh.h"
#include "ReadFiles.h"
#include "ReadFiles.h"
#include "MeshRaw.h"
using std::vector;

	MeshRaw::MeshRaw(float* vertices, size_t vertSize, size_t* indices, size_t indexSize, vec3ui* atribCounts, size_t atribCount) {
		this->atribCounts = vector<vec3ui>(atribCounts, atribCounts + atribCount);
		this->vertices = vector<float>(vertices, vertices + vertSize);
		this->indices = vector<size_t>(indices, indices + indexSize);

	}

	MeshRaw::MeshRaw(vector<float> vertices, vector<size_t> indices, vector<vec3ui> atribCounts) {
		this->vertices = vertices;
		this->indices = indices;
		this->atribCounts = atribCounts;
	}



	MeshRaw::MeshRaw(Mesh mesh, vector<vec3ui> atribCounts) {
		this->atribCounts = atribCounts;
		this->vertices = vector<float>(&mesh.vertices[0].x, &mesh.vertices[0].x + mesh.vertices.size());
		this->indices = mesh.indices;
	}

	MeshRaw::MeshRaw(Mesh mesh, vec3ui* atribCounts, size_t atribCount) {
		this->atribCounts = vector<vec3ui>(atribCounts, atribCounts + atribCount);
		this->vertices = vector<float>(&mesh.vertices[0].x, &mesh.vertices[0].x + mesh.vertices.size());
		this->indices = mesh.indices;
	}

	MeshRaw::MeshRaw(Mesh mesh) {
		//this->vertices = vector<float>(&mesh.vertices, &mesh.vertices + mesh.vertices.size());
		name = mesh.name;
		this->indices = mesh.indices;
		size_t countOfTotalAtribCounts = 0;
		size_t offset = 0;
		if (mesh.vertices.size() > 0) {
			//atribCounts.push_back(vec3ui(0, 3, offset));
			atribCounts.push_back(vec3ui(0, sizeof(mesh.vertices[0]) / sizeof(mesh.vertices[0].x), offset));
			offset += sizeof(mesh.vertices[0]);
			countOfTotalAtribCounts += atribCounts[atribCounts.size() - 1].y;
		}
		if (mesh.uvs.size() > 0) {
			//atribCounts.push_back(vec3ui(1, 3, offset));
			atribCounts.push_back(vec3ui(1, sizeof(mesh.uvs[0]) / sizeof(mesh.uvs[0].x), offset));
			offset += sizeof(mesh.uvs[0]);
			countOfTotalAtribCounts += atribCounts[atribCounts.size() - 1].y;
		}

		vertices.resize(countOfTotalAtribCounts * mesh.vertices.size());
		size_t k = 0;
		size_t i = 0;
		while (k < mesh.vertices.size())
		{
			vertices[i++] = mesh.vertices[k][0];
			vertices[i++] = mesh.vertices[k][1];
			vertices[i++] = mesh.vertices[k][2];

			if (mesh.uvs.size() > 0) {
				vertices[i++] = mesh.uvs[k][0];
				vertices[i++] = mesh.uvs[k][1];
			}
			k++;
		}
		//this->vertices = vector<float>(&mesh.vertices[0].x, &mesh.vertices[0].x + mesh.vertices.size()*3);
	}
	
	MeshRaw::MeshRaw() {}

	void MeshRaw::DestroyMesh() {
		delete[] &vertices;
		delete[] &indices;
		delete[] &atribCounts;
	}
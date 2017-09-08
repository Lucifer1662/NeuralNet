#pragma once
#include "Camera.h"
#include "MeshLoaded.h"
#include "MeshRaw.h"
#include "Export.h"

//__import void LoadLevel();




namespace Engine {
	extern API Camera* mainCamera;
	extern vector<GameObject*> gameObjects;

	extern GLuint vertexBuffer;
	extern GLuint indexBuffer;
	extern vector<MeshLoaded*> meshLoads;
	extern MeshLoaded* meshSquare;
	API extern void (*LoadLevel)();
	//extern void LoadLevel();

	void Render();
	void Setup();
	void Terminate();

	void RenderMeshLoaded(MeshLoaded mesh);
	void RenderMeshLoaded(MeshLoaded mesh, GLuint vbo, GLuint ibo);
	MeshLoaded* LoadMesh(MeshRaw mesh, GLuint vbo = -1, GLuint ibo = -1);
	void ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer);
	API GameObject* Instantiate(vec3 position, vec3 rotation, vec3 scale = vec3(1, 1, 1));
}




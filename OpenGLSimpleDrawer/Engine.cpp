#include "Engine.h"
#include "Platform.h"
#include "Program.h"
#include "Platform.h"
#include "Event.h"
//#include <dlfcn.h>

API Camera* Engine::mainCamera;
vector<GameObject*> Engine::gameObjects;

GLuint Engine::vertexBuffer;
GLuint Engine::indexBuffer;

vector<MeshLoaded*> Engine::meshLoads;
MeshLoaded* Engine::meshSquare;
//API void (*Engine::LoadLevel)();

//void(*LoadLevel)();

API void(*Engine::LoadLevel)();

void Engine::Setup() {
#pragma region OpenGlSetup
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
#pragma endregion
	//Create Default Shapes
#pragma region Create Square
	vec3 positions[4];
	positions[0] = vec3(-0.5f, -0.5f, 0);
	positions[1] = vec3(-0.5f, 0.5f, 0);
	positions[2] = vec3(0.5f, 0.5f, 0);
	positions[3] = vec3(0.5f, -0.5f, 0);

	size_t indices[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;


	Mesh squareMesh = Mesh(positions,4, indices, 6);
	squareMesh.name = "Square";
	squareMesh.uvs.resize(4);
	squareMesh.uvs[0] = vec2(0, 0);
	squareMesh.uvs[1] = vec2(0, 1);
	squareMesh.uvs[2] = vec2(1, 1);
	squareMesh.uvs[3] = vec2(1, 0);

	meshSquare = LoadMesh(squareMesh);
#pragma endregion
	printf("Before");
	//*(void **)(&LoadLevel) = dlsym(RTLD_DEFAULT, "RTAppUpdate");
	LoadLevel();
	
	/*GameObject* cameraObj = Instantiate(vec3(0, 0, 0), vec3(0, 0, 0));
	Engine::mainCamera = cameraObj->AddComponent<Camera>();



	//Load the level
	GameObject* testSqaureBlue = Instantiate(vec3(0, 0, 3), vec3(0, 0, 0));
	testSqaureBlue->AddComponent<SpriteRenderer>()->texture = Texture2D::CreateTexture("texture1.png", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

	GameObject* textGameObject = Instantiate(vec3(-1, 0.75f, 0), vec3(0, 0, 0));
	textGameObject->AddComponent<FPS>();
	*/
	
	printf("Start");
	//Call Start
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->CallStart();
	}
}


//Render the Scene
void Engine::Render() {
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->CallUpdate();
	}

	for(size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->CallRender();
	}
	
}



GameObject* Engine::Instantiate(vec3 position, vec3 rotation, vec3 scale){
	gameObjects.push_back(new GameObject());
	GameObject* gameObject = gameObjects[gameObjects.size() - 1];
	gameObject->transform->SetPosition(position);
	gameObject->transform->SetRotation(rotation);
	gameObject->transform->SetScale(scale);	
	return gameObject;
}
void Engine::RenderMeshLoaded(MeshLoaded meshLoaded, GLuint vbo, GLuint ibo) {
	size_t i = 0;
	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glEnableVertexAttribArray(meshLoaded.atribCounts[i].x);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glVertexAttribPointer(meshLoaded.atribCounts[i].x, meshLoaded.atribCounts[i].y, GL_FLOAT, GL_FALSE,
			meshLoaded.stride, (void*)(meshLoaded.atribCounts[i].z));

	glDrawElements(GL_TRIANGLES, meshLoaded.indexCount, GL_UNSIGNED_INT, (void*)(meshLoaded.indexOffset));

	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glDisableVertexAttribArray(meshLoaded.atribCounts[i].x);

}
void Engine::RenderMeshLoaded(MeshLoaded meshLoaded) {
	size_t i = 0;
	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glEnableVertexAttribArray(meshLoaded.atribCounts[i].x);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glVertexAttribPointer(meshLoaded.atribCounts[i].x, meshLoaded.atribCounts[i].y, GL_FLOAT, GL_FALSE,
			meshLoaded.stride, (void*)(meshLoaded.atribCounts[i].z));
	
	glDrawElements(GL_TRIANGLES, meshLoaded.indexCount, GL_UNSIGNED_INT, (void*)(meshLoaded.indexOffset));

	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glDisableVertexAttribArray(meshLoaded.atribCounts[i].x);
}


MeshLoaded* Engine::LoadMesh(MeshRaw mesh,GLuint vbo, GLuint ibo) {
	GLuint sizeOfVertexes = 0;
	GLuint sizeOfIndexes = 0;
	for (GLuint i = 0; i < meshLoads.size(); i++)
	{
		sizeOfVertexes += meshLoads[i]->vertexCount;
		sizeOfIndexes += meshLoads[i]->indexCount;
	}
	if (vbo == -1)
		vbo = vertexBuffer;
	if (ibo == -1)
		ibo = indexBuffer;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	if (sizeOfVertexes > 0) {
		ResizeBuffers(sizeOfVertexes * sizeof(GLfloat), (sizeOfVertexes + mesh.vertices.size()) * sizeof(GLfloat), &vertexBuffer, GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfVertexes * sizeof(GLfloat), mesh.vertices.size() * sizeof(GLfloat), &(mesh.vertices[0]));
	}
	else
		glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(GLfloat), &(mesh.vertices[0]), GL_DYNAMIC_DRAW);


	if (sizeOfIndexes > 0) {
		ResizeBuffers(sizeOfIndexes * sizeof(GLuint), (sizeOfIndexes + mesh.indices.size()) * sizeof(GLuint), &indexBuffer, GL_ELEMENT_ARRAY_BUFFER);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndexes * sizeof(GLuint), mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]));
	}
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);



	MeshLoaded* meshLs = new MeshLoaded();
	meshLs->indexCount = mesh.indices.size();
	meshLs->vertexCount = mesh.vertices.size();
	meshLs->indexOffset = sizeOfIndexes * sizeof(GLuint);
	//meshLs->vertexOffset = sizeOfVertexes * sizeof(GLfloat);
	meshLs->atribCounts = mesh.atribCounts;
	meshLs->name = mesh.name;

	GLuint vertModelOffset = sizeOfVertexes * sizeof(GLfloat);


	GLuint offset = 0;
	if (mesh.atribCounts.size() > 1)
		for (GLuint i = 0; i < mesh.atribCounts.size(); i++) {
			meshLs->stride += sizeof(mesh.vertices[offset]) * mesh.atribCounts[i].y;
			offset += mesh.atribCounts[i].y;
			meshLs->atribCounts[i].z += vertModelOffset;
		}
	else
		meshLs->stride = 0;

	if(vbo == -1)
		meshLoads.push_back(meshLs);
	return meshLs;
}



void Engine::ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer) {
	GLuint vbotemp;

	glBindBuffer(buffer, *bo);

	//create a temp buffer of type GL_COPY_READ_BUFFER
	glGenBuffers(1, &vbotemp);
	glBindBuffer(GL_COPY_READ_BUFFER, vbotemp);
	glBufferData(GL_COPY_READ_BUFFER, newSize, NULL, GL_STATIC_COPY);

	//copy data from vbo1 to it
	glCopyBufferSubData(buffer, GL_COPY_READ_BUFFER, 0, 0, oldSize);
	glBindBuffer(buffer, vbotemp);
	//glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);

	glDeleteBuffers(1, bo);
	bo[0] = vbotemp;
	
}

void Engine::Terminate() {
	Program::TermaniteAllPrograms();

	if (vertexBuffer != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vertexBuffer);
		vertexBuffer = 0;
	}

	if (indexBuffer != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &indexBuffer);
		indexBuffer = 0;
	}

	for (size_t i = 0; i < Engine::gameObjects.size(); i++)
	{
		delete Engine::gameObjects[i];
	}
	Engine::gameObjects.resize(0);

	for (size_t i = 0; i < Engine::meshLoads.size(); i++)
	{
		delete Engine::meshLoads[i];
	}
	Engine::meshLoads.resize(0);

// delete Engine::meshSquare
}



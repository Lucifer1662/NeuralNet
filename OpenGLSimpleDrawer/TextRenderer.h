#pragma once
#include "Component.h"
#include "Font.h"
#include "FontProgram.h"
#include "Mesh.h"
#include "MeshRaw.h"
#include "MeshLoaded.h"

class API TextRenderer : public Component {
	FontProgram* frProgram;
	GLfloat* points;
	Mesh* mesh;
	GLuint vbo;
	GLuint ibo;
	MeshRaw CreateMeshDataForRender();
	MeshLoaded* textMesh;
	friend void windowChangedTextRenderer(void* obj, int w, int h);	

public:
	float size = 1;
	vec3 color;
	Font* font;
	string text;
	TextRenderer();
	~TextRenderer();
	void Start();
	void Render();
	void SetText(string text);
	void RefreshText();
};

void windowChangedTextRenderer(void* obj, int w, int h);
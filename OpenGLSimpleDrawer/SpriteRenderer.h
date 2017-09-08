#pragma once
#include "Component.h"
#include "MeshLoaded.h"
#include "Texture2D.h"
#include "SpriteRendererProgram.h"

class API SpriteRenderer : public Component {
	static SpriteRendererProgram*  srProgram;

public:
    SpriteRenderer();
	~SpriteRenderer();
	void Start();
    void Render();
	void Update();	
    
	Texture2D* texture;
};



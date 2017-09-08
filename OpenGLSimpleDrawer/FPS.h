#pragma once
#include "TextRenderer.h"
class API FPS :	public TextRenderer {
public:
	FPS();
	~FPS();
	float counter;
	void Update();
};


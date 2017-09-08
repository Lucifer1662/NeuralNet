#include "SpriteRenderer.h"
#include "gtc/matrix_transform.hpp"
#include "Engine.h"
#include "SpriteRenderer.h"
#include "SpriteRendererProgram.h"


SpriteRendererProgram* SpriteRenderer::srProgram;

SpriteRenderer::SpriteRenderer() {
	
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Start() {
	srProgram = Program::GetProgram<SpriteRendererProgram>();
}

void SpriteRenderer::Render() { 
	srProgram->PreRenderSetup();
	srProgram->SetTransform(gameObject->transform);
	texture->BindTexture(0);
	Engine::RenderMeshLoaded(*Engine::meshSquare);
}

void SpriteRenderer::Update() { 
}


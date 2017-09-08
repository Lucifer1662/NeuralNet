#include "DotRenderer.h"
#include "gtc/matrix_transform.hpp"
#include "Engine.h"
#include "SpriteRendererProgram.h"


SpriteRendererProgram* DotRenderer::drProgram;


void DotRenderer::Start() {
	drProgram = Program::GetProgram<SpriteRendererProgram>();
}

void DotRenderer::Render() {
	drProgram->PreRenderSetup();
	Engine::RenderMeshLoaded(*Engine::meshSquare);
}

void SpriteRenderer::Update() {
}


DotRenderer::DotRenderer()
{
}


DotRenderer::~DotRenderer()
{
}

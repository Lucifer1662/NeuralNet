#include "TextRenderer.h"
#include "Mesh.h"
#include "Window.h"
#include "Engine.h"
using glm::vec3;
using glm::vec4;

#define VERTEXCOUNT 4

void TextRenderer::Start() {
	Window::windowChangedEvent.Add(this, windowChangedTextRenderer);


	frProgram = Program::GetProgram<FontProgram>();
	size = 100;

	text = "Hello World";
	//i should do static string
	//have max dynamic string
	//infinte string
	glGenBuffers(1, &vbo);

	glGenBuffers(1, &ibo);
	textMesh = Engine::LoadMesh(CreateMeshDataForRender(),vbo,ibo);

}


void TextRenderer::Render() {
	//the renderer creates an array of points with the Font characters
	//it handles the positions
	//the glsl program can handle creating the planes
	gameObject->transform->UpdateModelMat();
	frProgram->PreRenderSetup();
	frProgram->SetTransform(gameObject->transform->modelMatrix);
	font->texture->BindTexture(0);
	Engine::RenderMeshLoaded(*textMesh, vbo, ibo);	


}


MeshRaw TextRenderer::CreateMeshDataForRender() {
	Mesh mesh = Mesh();
	mesh.vertices.resize(text.size() * VERTEXCOUNT);
	mesh.indices.resize(text.size() * 6);
	mesh.uvs.resize(text.size() * VERTEXCOUNT);
	float cursor = 0;
	float line = 0;
	vec2ui texsize = font->texture->size;
	float w = (Window::width /2) * font->GetSize()/size;
	float h = (Window::height/2) * font->GetSize()/size;
	int i, k;
	for (int j = 0; j < text.size(); j++)
	{
		if (text[j] == '\n') {
			line += font->GetLineHeight();
			cursor = 0;
			continue;
		}

		FontCharacter fontCharacter = font->GetFontCharacter(text[j]);
		if (text[j] != ' ') {
			i = j * 4;

			vec3 mid = vec3((cursor + (float)fontCharacter.xoffset),
				(-(float)fontCharacter.yoffset - (float)line),
				gameObject->transform->GetPosition().z);


			vec2 adjSize = vec2((float)fontCharacter.width, (float)fontCharacter.height);
			vec2 uvadjSize = vec2(adjSize.x/texsize.x,adjSize.y/texsize.y);
			vec2 gUv = vec2((float)fontCharacter.x/texsize.x, (float)fontCharacter.y/texsize.y);

			

			//--------------------------------------------------
			vec3 p = (vec4(mid.x + adjSize.x, mid.y, mid.z, 1.0));
			vec2 uv = gUv + vec2(uvadjSize.x, 0);
			p.x /= w;
			p.y /= h;
			mesh.vertices[i] = p;
			mesh.uvs[i] = uv;
			//--------------------------------------------------
			p = vec4(mid, 1);
			uv = gUv;
			p.x /= w;
			p.y /= h;
			mesh.vertices[i + 1] = p;
			mesh.uvs[i + 1] = uv;
			//--------------------------------------------------
			mid.y -= adjSize.y; // this cause the next two to only be done once and not twice
			p = (vec4(mid.x + adjSize.x, mid.y, 0.0, 1.0));
			uv = gUv + uvadjSize;
			p.x /= w;
			p.y /= h;
			mesh.vertices[i + 2] = p;
			mesh.uvs[i + 2] = uv;
			//--------------------------------------------------
			p = (vec4(mid.x, mid.y, 0.0, 1.0));
			uv = gUv + vec2(0, uvadjSize.y);
			p.x /= w;
			p.y /= h;
			mesh.vertices[i + 3] = p;
			mesh.uvs[i + 3] = uv;
			//--------------------------------------------------
			

			k = 6 * j;	
	
			mesh.indices[k] = i + 1;
			mesh.indices[k + 1] = i;
			mesh.indices[k + 2] = i + 2;
			mesh.indices[k + 3] = i + 3;
			mesh.indices[k + 4] = i + 1;
			mesh.indices[k + 5] = i + 2;
			
		}
		cursor += ((float)fontCharacter.xadvance );
	}


	return MeshRaw(mesh);
}




TextRenderer::TextRenderer()
{
	font = new Font("Arial");
}

void TextRenderer::SetText(string text) {
	this->text = text;
	RefreshText();
}

void TextRenderer::RefreshText() {

	textMesh = Engine::LoadMesh(CreateMeshDataForRender(), vbo, ibo);	
}

void windowChangedTextRenderer(void* obj, int w, int h) {
	((TextRenderer*)obj)->RefreshText();	
}


TextRenderer::~TextRenderer()
{
}

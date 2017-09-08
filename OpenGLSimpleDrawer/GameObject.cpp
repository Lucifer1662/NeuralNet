#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Engine.h"

GameObject::GameObject(){
	transform = AddComponent<Transform>();
}

GameObject::~GameObject() {
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
	components.resize(0);
}

void GameObject::CallStart() {
	for (GLuint i = 0; i < components.size(); i++)
	{
		components[i]->Start();
	}
}

void GameObject::CallRender(){
    for (GLuint i = 0; i < components.size(); i++) {
        components[i]->Render();
    }
}

void GameObject::CallUpdate() {
	for (GLuint i = 0; i < components.size(); i++) {
		components[i]->Update();
	}
}
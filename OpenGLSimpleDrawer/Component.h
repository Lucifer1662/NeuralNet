#pragma once
#include "Export.h"
class GameObject;


class API Component {
public:
	GameObject* gameObject;
	virtual void Render() {}
	virtual void Update() {}
	virtual void Start() {}
	virtual void Destroy() {}
	virtual ~Component() {};
};


#include "GameObject.h"

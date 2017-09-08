#pragma once
#include "Transform.h"
#include "Component.h"


#include <vector>
using std::vector;

class Transform;


class API GameObject {
private:
    vector<Component*> components;
	
public:
	Transform* transform;
	
    GameObject();
    ~GameObject();
    void CallRender();
	void CallStart();
	void CallUpdate();

    template <class T> inline T* AddComponent(){
	   T* t = new T();
		t->gameObject = this;
        components.push_back(t);
        return t;
    }




};
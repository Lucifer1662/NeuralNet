#pragma once
#include "Component.h"
#include "glm.hpp"
#include "gtx/transform.hpp"
using glm::vec3;
using glm::mat4;

class API Transform : public Component {
private:
	mat4 _rotationMatrix;
	mat4 _translationMatrix;
	mat4 _scaleMatrix;
	mat4 _modelMatrix;

	vec3 _position;
	vec3 _rotation;
	vec3 _scale;

public:
	vec3 *const positionPointer; //Constant Pointer
	const mat4 &rotationMatrix; // Constant variable
	const mat4 &translationMatrix; // Constant variable
	const mat4 &scaleMatrix; // Constant variable
	const mat4 &modelMatrix; // Constant variable

	void UpdateModelMat() {
		_modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;
	}


	vec3 GetPosition() { return _position; }
	void SetPosition(vec3 position) {
		_position = position;
		_translationMatrix = glm::translate(glm::mat4(1.0f), _position);
		UpdateModelMat();
	}


	vec3 GetRotation() { return _rotation; }
	void SetRotation(vec3 rotation) {
		_rotation = rotation;
		_rotationMatrix =
			glm::rotate(_rotation.x, glm::vec3(1, 0, 0))
			* glm::rotate(_rotation.y, glm::vec3(0, 1, 0))
			* glm::rotate(_rotation.z, glm::vec3(0, 0, 1))
			;
		UpdateModelMat();
	}


	vec3 GetScale() { return _scale; }
	void SetScale(vec3 scale) {
		_scale = scale;
		_scaleMatrix = glm::scale(_scale);
		UpdateModelMat();
	}



	Transform() :
		modelMatrix(_modelMatrix),
		rotationMatrix(_rotationMatrix),
		translationMatrix(_translationMatrix),
		scaleMatrix(_scaleMatrix),		
		_scale(vec3(1, 1, 1)),
		positionPointer(&_position) {}


	~Transform() {}


};
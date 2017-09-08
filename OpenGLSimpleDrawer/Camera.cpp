#include "Camera.h"
#include "Engine.h"
#include "gtx\transform.hpp"
#include "Window.h"

mat4 Camera::getViewMatrix() {
	return perspectiveMatrix * glm::lookAt(
		*position, // Camera is at (4,3,3), in World Space
		*position - direction, // and looks at the origin
		up  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

void Camera::Start(){ 
	perspectiveMatrix = glm::ortho(-size, size, -size, size, 0.01f, 10.0f);
	Engine::mainCamera = this;
	position = gameObject->transform->positionPointer;
}

Camera::Camera()
{	

	
	
}

void Camera::ResetRatio(float width, float height) {
	//perspectiveMatrix = glm::perspective(3.141f / 2, width/height, 0.01f, 100.0f);

}


Camera::~Camera()
{
	
}

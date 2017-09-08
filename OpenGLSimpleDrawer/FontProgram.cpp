#include "FontProgram.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "Window.h"
#include "Engine.h"

mat4 FontProgram::screenMat;

FontProgram::FontProgram()
{
	

}


FontProgram::~FontProgram()
{
}

GLuint FontProgram::CreateProgram() {
	vector<ShaderSource> sources;
	ShaderSource source;
	source.filePath = "Shader/vertexShaderText.gl";
	source.shaderType = GL_VERTEX_SHADER;
	sources.push_back(source);

	source.filePath = "Shader/fragmentShaderText.gl";
	source.shaderType = GL_FRAGMENT_SHADER;
	sources.push_back(source);

	this->_CreateProgram(sources);
	Use();


	transformMatLocation = glGetUniformLocation(program, "transformMat");
	viewMatLocation = glGetUniformLocation(program, "viewMat");
	glUniform1i(glGetUniformLocation(program, "sampler1"), 0);


	screenMat = glm::scale(glm::vec3(8.0f / Window::width, 8.0f / Window::height, 1));
	return _program;
}

void FontProgram::SetTransform(glm::mat4 transformMat, bool isOnScreen) {
	Use();
	glUniformMatrix4fv(transformMatLocation, 1, GL_FALSE, &transformMat[0][0]);
	if (!isOnScreen) {
		glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, &Engine::mainCamera->getViewMatrix()[0][0]);
	}
	else {		
		glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, &screenMat[0][0]);
	}
}

void FontProgram::PreRenderSetup() {
	Use();
}
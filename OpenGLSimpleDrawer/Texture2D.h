#pragma once
#include <vector>
#include "vec2ui.h"
#include <string>
#include "glm.hpp"
#include "Platform.h"
#include "Export.h"


using std::string;
using std::vector;

class API Texture2D{
private:
	static vector<Texture2D*> loadedTextures;

	GLuint textureObject;
	
	void LoadTexture(char* filepath);
	void LoadTexture(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	void LoadTexture(const char* filepath, GLint internalFormat, GLenum format, GLenum type, GLenum target = GL_TEXTURE_2D, GLint level = 0);
	void SetPixelData(unsigned char* data);
	void UnLoadTexture();
	Texture2D();

	GLuint inComponents;
	GLuint outComponents;
	GLuint dataType;

public:
	vec2ui size;
	string name;
	static Texture2D* CreateTexture(char* filepath, GLint internalFormat, GLenum format, GLenum type, GLenum target = GL_TEXTURE_2D, GLint level = 0);



	void Clear(glm::vec4 clearColor);
	void Resize(vec2ui size);

	void BindTexture(GLuint textureLocation);	
	void Bind();
	void TexParameteri(GLuint pname, GLuint param);
	void BindFrameBuffer(GLuint attachment, GLint level);
	~Texture2D();
};


#include "Texture2D.h"
#include "ReadFiles.h"
#include "string"
#include "Window.h"
using std::string;

vector<Texture2D*> Texture2D::loadedTextures;

Texture2D::Texture2D() {}


void Texture2D::SetPixelData(unsigned char* data) {

}

void Texture2D::Clear(glm::vec4 clearColor) {
	//glClearTexImage(textureObject, 0, inComponents, GL_UNSIGNED_BYTE, &clearColor);
}

void Texture2D::BindTexture(GLuint textureLocation) {
	if (this)
		glBindTexture(GL_TEXTURE_2D, textureObject);
	else
		glBindTexture(GL_TEXTURE_2D, -1);

	glActiveTexture(GL_TEXTURE0 + textureLocation);
}


void Texture2D::BindFrameBuffer(GLuint attachment, GLint level) {
	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureObject, level);
	//glFramebufferTexture(GL_FRAMEBUFFER, attachment, textureObject, level);

}

void Texture2D::Bind() {
	glBindTexture(GL_TEXTURE_2D, textureObject);
}
void Texture2D::TexParameteri(GLuint pname, GLuint param) {
	glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Texture2D::LoadTexture(const char* filename, GLint internalFormat, GLenum format, GLenum type, GLenum target, GLint level) {
	const unsigned char* data = new unsigned char[0];
	glGenTextures(1, &textureObject);
	glBindTexture(GL_TEXTURE_2D, textureObject);

	inComponents = internalFormat;
	outComponents = format;
	dataType = type;

	string s = filename;


	char ext[4];
	ext[0] = filename[s.size() - 3];
	ext[1] = filename[s.size() - 2];
	ext[2] = filename[s.size() - 1];
	ext[3] = '\0';

	string extension = ext;

	if (extension == "png") {
		data = ReadPNG(filename, &size.x, &size.y);
	}
	else if (extension == "bmp") {
		data = ReadBMP(filename, &size.x, &size.y);
	}
	
	glTexImage2D(GL_TEXTURE_2D,level,internalFormat, size.x, size.y, 0,format, type, data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//------Cleaning up-------
	delete[] data;
}



Texture2D* Texture2D::CreateTexture(char* fileName, GLint internalFormat, GLenum format, GLenum type, GLenum target, GLint level) {
	bool failed = false;
	size_t count = -1;
	do {
		failed = false;
		for (size_t i = 0; i < loadedTextures.size(); i++)
		{
			if (loadedTextures[i]->name == fileName) {
				failed = true;
				break;
			}
		}
		count++;
	} while (failed);
	if (count != 0) {
		fileName += '(';
		fileName += count;
		fileName += ')';
		//std::cout << "Texture name was the same as another creating new name" << name << std::endl;
	}

	loadedTextures.push_back(new Texture2D());
	Texture2D* texture = loadedTextures[loadedTextures.size() - 1];
	texture->LoadTexture(fileName, internalFormat, format, type, target, level);
	return texture;
}

void Texture2D::Resize(vec2ui size) {
	glBindTexture(GL_TEXTURE_2D, textureObject);
	glTexImage2D(GL_TEXTURE_2D, 0, inComponents, size.x, size.y, 0, outComponents, dataType, 0);
}

void Texture2D::UnLoadTexture() {
	glDeleteTextures(1, &textureObject);
}

Texture2D::~Texture2D()
{
	UnLoadTexture();
}

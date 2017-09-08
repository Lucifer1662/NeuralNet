#pragma once
#include <string>
#include "Platform.h"
#include "MeshRaw.h"
#include <string>
//#include "SoundData.h"

using std::string;

std::string ReadFile(string filePath);
void ReadFile(void* buffer, GLuint bytesize, GLuint length, string fileFullPath);
//SoundData ReadWAV(const char* fileName);
const unsigned char* ReadPNG(const char* filename, GLuint* width, GLuint* height);
const unsigned char* ReadBMP(const char* filename, GLuint* width, GLuint* height);
MeshRaw ReadFromHObj(const char * destination);

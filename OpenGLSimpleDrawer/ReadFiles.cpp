
#include <string>
#include "lodepng.h"
#include "vec2ui.h"
#include "soundfile-2.2\include\SoundFileRead.h"
#include "ReadFiles.h"
#include "IO.h"
//#include <al.h>
#include "MeshRaw.h"

class ifstream;

using std::cout;
using std::endl;
using std::string;

string ReadFile(string filePath) {
	void* file = NULL;
	int error;
	std::istream* ifs = openStringStream(file, filePath.c_str(), error);
	std::string str((std::istreambuf_iterator<char>(*ifs)), std::istreambuf_iterator<char>());
	close(file);
	return str;
}

void ReadFile(void* buffer, GLuint bytesize, GLuint length, string fileFullPath) {

	void* file = NULL;
	int error = open(file, fileFullPath.c_str());
	if (error != 0) {
		cout << "Failed to open file, error :" << error;
		return;
	}
	
	read((void*)buffer, bytesize, length, file);

	close(file);
}

const unsigned char* ReadBMP(const char* filename, GLuint* width, GLuint* height)
{

	const unsigned char* header = new unsigned char[54];
	
	void* file = NULL;
	open(file, filename);

	read((void*)header, 1, 54,file);

	// extract image height and width from header
	height[0] = *(int*)&header[0x12];
	width[0] = *(int*)&header[0x16];
	GLuint dataPos = *(int*)&(header[0x0A]);
	if (dataPos == 0)
		dataPos = 54;

	GLuint size = *(int*)&(header[0x22]) + dataPos;
	//  if(size == 0)
	size = dataPos + 3 * width[0] * height[0];


	unsigned char* data = new unsigned char[size];
	read((void*)data, 1, size, file);


	for (int i = dataPos; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}


	close(file);
	delete[] header;
	return data;
}

const unsigned char* ReadPNG(const char* filename, GLuint* width, GLuint* height)
{

	std::vector<unsigned char> image;
	unsigned int widthi, heighti;
	//decode
	unsigned error = lodepng::decode(image, widthi, heighti, filename);

	if (error != 0)
	{
		std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		return NULL;
	}
	width[0] = widthi;
	height[0] = heighti;

	unsigned char* result = new unsigned char[image.size()];
	memcpy(result, &image[0], image.size());
	return result;
}



MeshRaw ReadFromHObj(const char * destination) {
	MeshRaw raw = MeshRaw();
	raw.name = "sphere.Hobj";
	void* file = NULL;
	int error;
	istream* stream = openStringStream(file, destination, error);
	//std::ifstream istream(destination);

	size_t vertSize;
	size_t indiceSize;
	size_t atribSize;

	*stream >> vertSize;
	*stream >> indiceSize;
	*stream >> atribSize;

	raw.atribCounts = vector<vec3ui>(atribSize);
	for (size_t i = 0; i < atribSize; i++)
	{
		*stream >> raw.atribCounts[i].x;
		*stream >> raw.atribCounts[i].y;
		*stream >> raw.atribCounts[i].z;

	}

	raw.vertices = vector<float>(vertSize);
	for (size_t i = 0; i < vertSize; i++)
	{
		*stream >> raw.vertices[i];
	}

	raw.indices = vector<size_t>(indiceSize);
	for (size_t i = 0; i < indiceSize; i++)
	{
		*stream >> raw.indices[i];
	}


	/*istream.read((char*)&vertSize, 4);
	istream.read((char*)&indiceSize, 4);
	istream.read((char*)&atribSize, 4);

	size_t* atribBuffer = new size_t[atribSize * 3];
	istream.read((char*)atribBuffer, atribSize * 12);
	raw.atribCounts = vector<vec3ui>(atribSize);

	for (size_t i = 0; i < atribSize * 3; i += 3) {
	raw.atribCounts[g].x = atribBuffer[i];
	raw.atribCounts[g].y = atribBuffer[i+1];
	raw.atribCounts[g].z = atribBuffer[i+2];
	g++;
	}

	delete[] atribBuffer;

	raw.vertices = vector<float>(vertSize);
	istream.read((char*)&raw.vertices.data()[0], 50 * 4);
	istream.read((char*)&raw.vertices.data()[50], 50 * 4);
	istream.
	raw.indices = vector<size_t>(indiceSize);
	size_t* b = new size_t[indiceSize];
	//	istream.read((char *)indiceSize, indiceSize * 4);

	istream.read((char *)raw.indices.data(), indiceSize * 4);

	for (size_t i = 0; i < indiceSize; i++)
	std::cout << raw.indices[i] << std::endl;
	*/

	closeStringStream(file);
	return raw;
}


/*

SoundData ReadWAV(const char* fileName) {
	SoundData soundData;

	string resourcePath = "C:/Users/lhawk/Stuff/VisualStudio/Engine/Debug/Resources/Sounds/";
	resourcePath.append(fileName);
	const char* fileDestination = resourcePath.c_str();

	void *fp = NULL;                                                            //Create FILE pointer for the WAVE file
	FileIO i;
	

	open(&fp, fileDestination);                                            //Open the WAVE file
	if (!fp) {
		std::cout << "Could not open file" << std::endl;
		//return soundData;
	}

	//Variables to store info about the WAVE file (all of them is not needed for OpenAL)
	char type[4];
	size_t size, chunkSize;
	short formatType, channels;
	size_t sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	size_t dataSize;
	

	//Check that the WAVE file is OK

	read(type, sizeof(char), 4, fp);                                              //Reads the first bytes in the file
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')            //Should be "RIFF"
		std::cout << "No RIFF" << std::endl;                                         //Not RIFF

	read(&size, sizeof(size_t), 1, fp);                                           //Continue to read the file
	read(type, sizeof(char), 4, fp);                                             //Continue to read the file
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')           //This part should be "WAVE"
		std::cout << "not WAVE" << std::endl;                                       //Not WAVE

	read(type, sizeof(char), 4, fp);                                              //Continue to read the file
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')           //This part should be "fmt "
		std::cout << "not fmt " << std::endl;                                            //Not fmt 

																						 //Now we know that the file is a acceptable WAVE file
																						 //Info about the WAVE data is now read and stored
	read(&chunkSize, sizeof(size_t), 1, fp);
	read(&formatType, sizeof(short), 1, fp);
	read(&channels, sizeof(short), 1, fp);
	read(&sampleRate, sizeof(size_t), 1, fp);
	read(&avgBytesPerSec, sizeof(size_t), 1, fp);
	read(&bytesPerSample, sizeof(short), 1, fp);
	read(&bitsPerSample, sizeof(short), 1, fp);

	read(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')           //This part should be "data"
		std::cout << "Missing DATA" << std::endl;                                      //not data

	read(&dataSize, sizeof(size_t), 1, fp);                                        //The size of the sound data is read

																					//Display the info about the WAVE file
	cout << "Chunk Size: " << chunkSize << "\n";
	cout << "Format Type: " << formatType << "\n";
	cout << "Channels: " << channels << "\n";
	cout << "Sample Rate: " << sampleRate << "\n";
	cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
	cout << "Bytes Per Sample: " << bytesPerSample << "\n";
	cout << "Bits Per Sample: " << bitsPerSample << "\n";
	cout << "Data Size: " << dataSize << "\n";

	soundData.data = new char[dataSize];                      //Allocate memory for the sound data
	cout << read(soundData.data, sizeof(char), dataSize, fp) << " bytes loaded\n";

	soundData.soundInformation.frequency = sampleRate;
	if (channels == 1) {
		if (bitsPerSample == 8)
			soundData.soundInformation.format = AL_FORMAT_MONO8;
		else if (bitsPerSample == 16)
			soundData.soundInformation.format = AL_FORMAT_MONO16;
	}
	else if (channels == 1) {
		if (bitsPerSample == 8)
			soundData.soundInformation.format = AL_FORMAT_STEREO8;
		else if (bitsPerSample == 16)
			soundData.soundInformation.format = AL_FORMAT_STEREO16;
	}
	soundData.size = dataSize;
	return soundData;
}

*/
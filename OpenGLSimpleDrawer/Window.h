#pragma once
#include "Platform.h"
#include "Event.h"
#include "Export.h"



namespace Window {
	API extern const char* applicationDirectory;

	extern unsigned int width;
	extern unsigned int height;
	extern Event<void, int, int> windowChangedEvent;

	void Terminate();
	void Render();
	void Setup();
}
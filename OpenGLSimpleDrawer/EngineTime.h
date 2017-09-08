#pragma once

#include "Window.h"
class EngineTime {
public:
	static void Start();
	static void Finish();
	static double _deltaTime;


	static const double &deltaTime;
};
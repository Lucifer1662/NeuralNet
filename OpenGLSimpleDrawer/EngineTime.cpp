
#include "EngineTime.h"

#include <chrono>
using namespace std::chrono;

high_resolution_clock::time_point t1;
high_resolution_clock::time_point t2;

double EngineTime::_deltaTime;
const double &EngineTime::deltaTime = _deltaTime;


void EngineTime::Start() {
	t1 = high_resolution_clock::now();
}

void EngineTime::Finish() {
	t2 = high_resolution_clock::now();
	long count = duration_cast<nanoseconds>(t2 - t1).count();
	_deltaTime = count / 1000000000.0f;
}
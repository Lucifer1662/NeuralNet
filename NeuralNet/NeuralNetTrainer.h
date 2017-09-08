#pragma once
#include "NeuralNet.h"
#include "InOut.h"
#include <vector>
using std::vector;

class __declspec(dllexport) NeuralNetTrainer
{
	NeuralNet* neuralNet;
public:
	bool stop;
	NeuralNetTrainer();
	NeuralNetTrainer(NeuralNet* net);
	~NeuralNetTrainer();
	void Train(vector<InOut> stimuluses);
	void TrainOnce(vector<InOut> stimuluses);
};


#pragma once
#include "Component.h"
#include "NeuralNet.h"
#include "NeuralNetTrainer.h"
#include "InOut.h"
#include <vector>
using std::vector;

class NeuralNetTrainerVisualizer :	public Component{
	NeuralNetTrainer trainer;
	vector<Transform*> inPoints, outPoints, currentPoints;
	vector<vector<Transform*>> grid;


public:
	NeuralNet* neuralNet;
	vector<InOut> data;
	NeuralNetTrainerVisualizer();
	~NeuralNetTrainerVisualizer();
	void Start();
	void Update();
};


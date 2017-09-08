#include "NeuralNet.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

NeuralNet::NeuralNet()
{

	
}


NeuralNet::~NeuralNet()
{
}

void NeuralNet::Init()
{
	//Initalise Shared Memory
	size_t sum = 0;
	size_t i;
	for (i = 0; i < nodes.size(); i++)
	{
		sum += nodes[i]->getDataSize(dimensionsBetweenNodes[i], dimensionsBetweenNodes[i + 1]);
	}

	nodeData = vector<double>(sum);
	size_t offset = 0;
	for (i = 0; i < nodes.size(); i++)
	{
		nodes[i]->Init(dimensionsBetweenNodes[i], dimensionsBetweenNodes[i + 1], (double*)(nodeData.data() + offset));
		offset += nodes[i]->getDataSize(dimensionsBetweenNodes[i], dimensionsBetweenNodes[i + 1]);
	}

}


void NeuralNet::NodesToIdentity() {
	for (size_t i = 0; i < nodes.size(); i++)
	{
		nodes[i]->ToIdentity();
	}
}

void NeuralNet::NodesToRandom() {
	for (size_t i = 0; i < nodes.size(); i++)
		nodes[i]->ToRandom();

}

Eigen::VectorXd NeuralNet::Evaluate(Eigen::VectorXd in)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		in = nodes[i]->Evaluate(in);
		
	}


	return in;
}







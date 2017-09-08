#pragma once
#include <Core>
#include <vector>
#include "Node.h"
#include <exception>
using std::vector;
using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::exception;


class __declspec(dllexport) NeuralNet
{
	vector<Node*> nodes;
	
	
	vector<size_t> dimensionsBetweenNodes;

public:
	vector<double> nodeData;

	NeuralNet();
	~NeuralNet();
	void Init();
	void NodesToRandom();
	void NodesToIdentity();
	template<typename T>
	void AddNode(size_t fromDimension, size_t toDimension) {
		if (dimensionsBetweenNodes.size() > 0) {		
			if (dimensionsBetweenNodes[dimensionsBetweenNodes.size() - 1] != fromDimension)
				throw new exception("Dimension Does Not Match Last Node");
			else {
				dimensionsBetweenNodes.push_back(toDimension);
			}
		}
		else {
			dimensionsBetweenNodes.push_back(fromDimension);
			dimensionsBetweenNodes.push_back(toDimension);		
		}

		 
		nodes.push_back(new T());
	}
	Eigen::VectorXd Evaluate(Eigen::VectorXd in);


};


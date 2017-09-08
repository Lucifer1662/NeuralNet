#pragma once
#include "Node.h"
using Eigen::MatrixXd;
using Eigen::VectorXd;

class __declspec(dllexport) LinearNode : public Node
{
	Eigen::Map<MatrixXd>* transformation;
public:
	LinearNode();
	void Init(const size_t fromDimension,const size_t toDimension, double* data);
	~LinearNode();
	VectorXd Evaluate(VectorXd vecin);
	size_t getDataSize(const size_t fromDimension, const size_t toDimension);
	void ToIdentity();
	void ToRandom(double min = 1, double max = 1);
};


#pragma once
#include <Core>
#include "Node.h"
using Eigen::VectorXd;

class __declspec(dllexport) ExponentialNode :	public Node
{
	Eigen::Map<VectorXd>* power;
public:
	ExponentialNode();
	~ExponentialNode();
	void Init(const size_t fromDimension, const size_t toDimension, double* data);
	VectorXd Evaluate(VectorXd vecin);
	size_t getDataSize(const size_t fromDimension, const size_t toDimension);
	void ToIdentity();
	void ToRandom(double min = 1, double max = 1);
};


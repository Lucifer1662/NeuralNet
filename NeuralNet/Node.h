#pragma once
#include <Core>
using Eigen::VectorXd;

class __declspec(dllexport) Node
{
public:
	~Node();
	virtual void Init(const size_t fromDimension, const size_t toDimension, double* data) = 0;
	virtual size_t getDataSize(const size_t fromDimension, const size_t toDimension) =0;
	virtual VectorXd Evaluate(VectorXd vecin) = 0;
	virtual void ToIdentity() = 0;
	virtual void ToRandom(double min = 1, double max = 1) = 0;
};


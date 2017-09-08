#include "ExponentialNode.h"
#include <iostream>


ExponentialNode::ExponentialNode()
{

}


ExponentialNode::~ExponentialNode()
{
}

void ExponentialNode::Init(const size_t fromDimension, const size_t toDimension, double * data)
{
	power = new Eigen::Map<VectorXd>(data, toDimension);
}

VectorXd ExponentialNode::Evaluate(VectorXd vecin)
{
	for (size_t i = 0; i < power->size(); i++)
	{
			if(vecin[i] >= 0)
				vecin[i] = pow(vecin[i], (*power)[i]);
			else
				vecin[i] = pow(abs(vecin[i]), (*power)[i])*-1;
	

		//vecin[i] = pow(abs(vecin[i]), (*power)[i]);

	}
	//std::cout << std::endl;
	return vecin;
}

size_t ExponentialNode::getDataSize(const size_t fromDimension, const size_t toDimension)
{
	return fromDimension;
}

void ExponentialNode::ToIdentity()
{
	for (size_t i = 0; i < power->size(); i++)
	{
		(*power)[i] = 1;
	}
}

void ExponentialNode::ToRandom(double min, double max)
{
	for (size_t i = 0; i < power->size(); i++)
	{
		(*power)[i] = 1;
	}
}

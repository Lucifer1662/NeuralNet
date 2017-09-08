#include "LinearNode.h"
#include <iostream>



LinearNode::LinearNode() {

}

void LinearNode::Init(const size_t fromDimension,const size_t toDimension, double* data)
{
	transformation = new Eigen::Map<MatrixXd>(data,toDimension,fromDimension);
}


LinearNode::~LinearNode()
{
}

VectorXd LinearNode::Evaluate(VectorXd vecin)
{
	
	return *transformation * vecin;
}

size_t LinearNode::getDataSize(const size_t fromDimension, const size_t toDimension)
{
	return fromDimension*toDimension;
}

void LinearNode::ToIdentity()
{
	transformation->setIdentity();
}

void LinearNode::ToRandom(double min, double max)
{
	transformation->setRandom();
}

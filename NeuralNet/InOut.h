#pragma once
#include <Core>
using Eigen::VectorXd;
struct __declspec(dllexport) InOut {
	VectorXd in;
	VectorXd out;
	InOut();
	InOut(VectorXd in, VectorXd out):in(in), out(out) {}
};
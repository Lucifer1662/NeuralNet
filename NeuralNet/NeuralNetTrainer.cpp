#include "NeuralNetTrainer.h"
#include <iostream>
using std::cout;
using std::endl;


NeuralNetTrainer::NeuralNetTrainer()
{
}

NeuralNetTrainer::NeuralNetTrainer(NeuralNet * net) :neuralNet(net)
{
}


NeuralNetTrainer::~NeuralNetTrainer()
{
}

void NeuralNetTrainer::Train(vector<InOut> stimuluses)
{
	stop = true;
	double delta = 0.01f;
	double fitness;
	double fitnessup;
	double fitnessdown;
	char initDirection = 3;
	bool direction;
	vector<bool> done = vector<bool>(
		neuralNet->nodeData.size()
		* stimuluses[0].out.size()
		* stimuluses.size()
		);
	size_t t = 0;

	for (size_t iteration = 0; iteration < 1; iteration++){
		
		//	size_t k = rand()% stimulus.out.size();
		//	
				//Optimize for each parameter
			while (stop) {
				for each (InOut stimulus in stimuluses){
				for (size_t k = 0; k < stimulus.out.size(); k++) {
					for (size_t i = 0; i < neuralNet->nodeData.size(); i++)
					{
						
						// get current fitness
						fitness = abs(stimulus.out[k] - neuralNet->Evaluate(stimulus.in)[k]);

						//change one parameter up and down
						//up
						neuralNet->nodeData[i] += delta;
						fitnessup = abs(stimulus.out[k] - neuralNet->Evaluate(stimulus.in)[k]);
						//fitnessup = (stimulus.out - neuralNet->Evaluate(stimulus.in)).lpNorm<1>();
						//down
						neuralNet->nodeData[i] -= 2 * delta;
						fitnessdown = abs(stimulus.out[k] - neuralNet->Evaluate(stimulus.in)[k]);
						//fitnessdown = (stimulus.out - neuralNet->Evaluate(stimulus.in)).lpNorm<1>();

						direction = fitnessup < fitnessdown;
						fitnessup = fmin(fitnessdown, fitnessup);
						if (fitness <= fitnessup) {
							done[t] = true;
							neuralNet->nodeData[i] += delta;
							t++;
							continue;
						}
						//check which is better

						//if first time
				/*		if (initDirection == 3)
							initDirection = direction;
						//if direction change
						if (direction != initDirection)
							break;
							*/
						cout << fitness << endl;
						//set better one as the value for the coeffecient
						if (direction)
							neuralNet->nodeData[i] += 2 * delta;
						//		else if (fitnessdown == fitnessup)
						//			break;
						t++;
					}
				}
				
			}
				//fitness = (stimulus.out - neuralNet->Evaluate(stimulus.in)).norm();
				//cout << fitness << endl;
					bool ret = true;
					for (size_t i = 0; i < done.size(); i++)
					{
						if (done[i] == false) {
							ret = false;
							break;
						}
					}
					if (ret)
						break;
					for (size_t i = 0; i < done.size(); i++)
					{
						done[i] = false;
					}
					t = 0;
			
			
		

		}
	} 

}

void NeuralNetTrainer::TrainOnce(vector<InOut> stimuluses)
{
	double fitness, fitnessup, fitnessdown, delta = 0.006f;
	bool direction;
	for each (InOut stimulus in stimuluses) {
		for (size_t k = 0; k < stimulus.out.size(); k++) {
			for (size_t i = 0; i < neuralNet->nodeData.size(); i++)
			{

				// get current fitness
				fitness = abs(stimulus.out[k] - neuralNet->Evaluate(stimulus.in)[k]);

				//change one parameter up and down
				//up
				neuralNet->nodeData[i] += delta;
				fitnessup = abs(stimulus.out[k] - neuralNet->Evaluate(stimulus.in)[k]);
				//fitnessup = (stimulus.out - neuralNet->Evaluate(stimulus.in)).lpNorm<1>();
				//down
				neuralNet->nodeData[i] -= 2 * delta;
				fitnessdown = abs(stimulus.out[k] - neuralNet->Evaluate(stimulus.in)[k]);
				//fitnessdown = (stimulus.out - neuralNet->Evaluate(stimulus.in)).lpNorm<1>();

				direction = fitnessup < fitnessdown;
				fitnessup = fmin(fitnessdown, fitnessup);
				//cout << fitness << endl;
				if (fitness <= fitnessup) {
					neuralNet->nodeData[i] += delta;
					continue;
				}
	
				
				//set better one as the value for the coeffecient
				if (direction)
					neuralNet->nodeData[i] += 2 * delta;
				//		else if (fitnessdown == fitnessup)
				//			break;

			}
		}

	}

}

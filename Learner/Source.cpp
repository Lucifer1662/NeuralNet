#define ENGINE_IMPORT
#include <NeuralNet.h>
#include <iostream>
#include <LinearNode.h>
#include <ExponentialNode.h>
#include "NeuralNetTrainer.h"
#include <thread>

#include <Engine.h>
#include "FPS.h"
#include "Engine.h"
#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "NeuralNetTrainerVisualizer.h"

#include "WindowsWindow.h"
#include "Engine.h"
#include <string>
using std::thread;
using std::cout;
using std::endl;

NeuralNetTrainer trainer;
/*
void Train() {
	VectorXd in = VectorXd(2);
	in[0] = 1;
	in[1] = 0.5;
	VectorXd out = VectorXd(2);
	out[0] = 0.25;
	out[1] = 3;

	vector<InOut> inOuts;
	inOuts.push_back(InOut(in, out));
	in[0] = 2;
	in[1] = -1;
	out[0] = 0.4;
	out[1] = 2;
	inOuts.push_back(InOut(in, out));
	in[0] = -1;
	in[1] = 4;
	out[0] = -1.4;
	out[1] = 0.9;
	inOuts.push_back(InOut(in, out));
	trainer.Train(inOuts);
}
*/
void LoadLevel() {
	std::cout << "LevelDLL" << std::endl;
	GameObject* cameraObj = Engine::Instantiate(vec3(0, 0, 10), vec3(0, 0, 0));
	Engine::mainCamera = cameraObj->AddComponent<Camera>();
	Engine::mainCamera->size = 10;
	//Load the level

	
	NeuralNet* net = new NeuralNet();

	

//	net->AddNode<ExponentialNode>(2, 2);
	net->AddNode<LinearNode>(2, 4);
	net->AddNode<LinearNode>(4, 6);
	net->AddNode<ExponentialNode>(6,6);
	net->AddNode<LinearNode>(6, 4);
	net->AddNode<ExponentialNode>(4, 4);
	net->AddNode<LinearNode>(4, 2);

	net->Init();
	net->NodesToRandom();

	VectorXd in = VectorXd(2);
	in[0] = 1;
	in[1] = 0.5;
	VectorXd out = VectorXd(2);
	out[0] = -2;
	out[1] = -3;

	vector<InOut> inOuts;
	inOuts.push_back(InOut(in, out));
	in[0] = -2;
	in[1] = -1;
	out[0] = -0.4;
	out[1] = 2;
	inOuts.push_back(InOut(in, out));
	in[0] = -1;
	in[1] = 4;
	out[0] = -1.4;
	out[1] = 0.9;
	inOuts.push_back(InOut(in, out));


	GameObject* neuralNetGameObject = Engine::Instantiate(vec3(1, 0, 0), vec3(0, 0, 0));
 	NeuralNetTrainerVisualizer* visualer = neuralNetGameObject->AddComponent<NeuralNetTrainerVisualizer>();
	visualer->neuralNet = net;
	visualer->data = inOuts;


}



using std::string;
void main(int argc, char* argv[]) {
	string temp = argv[0];
	temp.resize(temp.find_last_of('\\') + 1);
	temp.append("assets\\");
	Window::applicationDirectory = temp.c_str();
	Engine::LoadLevel = LoadLevel;
	WindowsWindow::Init(600, 600);
	WindowsWindow::StartRendering();
	/*
	NeuralNet net = NeuralNet();
	
//	net.AddNode<ExponentialNode>(2, 2);
//	net.AddNode<LinearNode>(2, 2);
	
	net.AddNode<LinearNode>(2, 2);

	//net.AddNode<LinearNode>(2, 6);
	//net.AddNode<LinearNode>(6, 6);
	//net.AddNode<ExponentialNode>(6, 6);
	//net.AddNode<LinearNode>(6, 2);

	net.Init();
	net.NodesToRandom();

	VectorXd in = VectorXd(2);
	in[0] = 1;
	in[1] = 0.5;
	VectorXd out = VectorXd(2);
	out[0] = 0.25;
	out[1] = 3;

	vector<InOut> inOuts;
	inOuts.push_back(InOut(in,out));
	in[0] = 2;
	in[1] = -1;
	out[0] = 0.4;
	out[1] = 2;
	inOuts.push_back(InOut(in, out));
	in[0] = -1;
	in[1] = 4;
	out[0] = -1.4;
	out[1] = 0.9;
	inOuts.push_back(InOut(in, out));

	trainer = NeuralNetTrainer(&net);
	//trainer.Train(inOuts);

	thread t = thread(Train);
	int p;
	std::cin >> p;
	
	trainer.stop = false;
	t.join();

	/*inOuts.clear();
	in[0] = 2;
	in[1] = -1;
	out[0] = 0.4;
	out[1] = 2;
	inOuts.push_back(InOut(in, out));
	trainer.Train(inOuts);*/

	/*
	for (size_t i = 0; i < inOuts.size(); i++) {
		cout << "IN:" << endl;
		cout << inOuts[i].in << endl << endl;
		cout << "Expected Out:" << endl;
		cout << inOuts[i].out << endl << endl;
		cout << "Out:" << endl;
		cout << net.Evaluate(inOuts[i].in) << endl << endl << endl;
	}

	for (size_t i = 0; i < net.nodeData.size(); i++)
	{
		cout << net.nodeData[i] << endl;
	}
	while (true) {}
	*/

}










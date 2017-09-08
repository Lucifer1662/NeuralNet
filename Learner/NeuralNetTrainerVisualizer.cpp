#pragma once
#include "NeuralNetTrainerVisualizer.h"
#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "Engine.h"



NeuralNetTrainerVisualizer::NeuralNetTrainerVisualizer()
{
}


NeuralNetTrainerVisualizer::~NeuralNetTrainerVisualizer()
{
}

void NeuralNetTrainerVisualizer::Start()
{
	trainer = NeuralNetTrainer(neuralNet);

	static int size = 30;
	grid.resize(size);
	for (size_t i = 0; i < grid.size(); i++)
	{
		grid[i].resize(size);
	}

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[0].size(); y++)
		{
			GameObject* tempObj = Engine::Instantiate(vec3(x - size / 2, y - size / 2, 0), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f));
			tempObj->AddComponent<SpriteRenderer>()->texture = Texture2D::CreateTexture("white.png", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
			grid[x][y] = tempObj->transform;

		}
	}

	//create all the new gameObjects
	inPoints.resize(data.size());
	outPoints.resize(data.size());
	currentPoints.resize(data.size());
	for (size_t i = 0; i < data.size(); i++)
	{
		vec3 p = vec3();
		for (size_t j = 0; j < data[i].in.size(); j++)
			p[j] = data[i].in[j];
		GameObject* tempObj = Engine::Instantiate(p, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f));
		tempObj->AddComponent<SpriteRenderer>()->texture = Texture2D::CreateTexture("red.png", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		inPoints[i] = tempObj->transform;

		p = vec3();
		for (size_t j = 0; j < data[i].out.size(); j++)
			p[j] = data[i].out[j];
		tempObj = Engine::Instantiate(p, vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f));
		tempObj->AddComponent<SpriteRenderer>()->texture = Texture2D::CreateTexture("green.png", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		outPoints[i] = tempObj->transform;

		tempObj = Engine::Instantiate(vec3(-1, 0, 0), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f));
		tempObj->AddComponent<SpriteRenderer>()->texture = Texture2D::CreateTexture("blue.png", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		currentPoints[i] = tempObj->transform;
	}

	
	

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[0].size(); y++)
		{
		//	GameObject* tempObj = Engine::Instantiate(vec3(x - size / 2, y - size / 2, 0), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f));
		//	tempObj->AddComponent<SpriteRenderer>()->texture = Texture2D::CreateTexture("red.png", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
			//grid[x][y] = tempObj->transform;

		}
	}

}

void NeuralNetTrainerVisualizer::Update()
{
	trainer.TrainOnce(data);
	for (size_t i = 0; i < data.size(); i++)
	{
		Eigen::VectorXd vec = neuralNet->Evaluate(data[i].in);
		vec3 p;
		for (size_t j = 0; j < vec.size(); j++)
			p[j] = vec[j];
		
		currentPoints[i]->SetPosition(p);
	}

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[0].size(); y++)
		{
			Eigen::VectorXd vec = Eigen::VectorXd(2);
			vec[0] = x-(int)grid.size()/2;
			vec[1] = y-(int)grid.size()/2;
			//std::cout << vec << std::endl << std::endl;
			vec = neuralNet->Evaluate(vec);
			vec3 p;
			for (size_t j = 0; j < vec.size(); j++)
				p[j] = vec[j]; 

			grid[x][y]->SetPosition(p);

		}
	}

}

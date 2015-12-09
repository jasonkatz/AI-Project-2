/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural network implementation
with one hidden layer

File: Network.h
Description: Neural network class
structure and declarations
*****************************************
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

class Network {

	class Node {

	public:

		Node() {
			activation = 0;
		}

		double activation, in, error;
		std::vector<double> weights;
	};

	std::vector<Node *> inputLayer, hiddenLayer, outputLayer;

	// Sigmoid
	double sigmoid(double);
	double sigmoidPrime(double);

public:

	// Default constructor
	Network() {}

	// Constructor that accepts vectors of nodes for each layer
	Network(std::vector<Node *>, std::vector<Node *>, std::vector<Node *>);

	// Train method for network
	// Reads training set from file and trains network
	// using back-prop-learning algorithm
	void Train(std::string, int, double);

	// Test method for network
	// Reads and evaluates testing set from file
	// and tests network performance
	// then saves results to a file
	void Test(std::string, std::string);

	// Static network load and save file methods
	static Network LoadFromFile(std::string);
	static void SaveToFile(std::string, Network);

};

#endif
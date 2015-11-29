/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural Network implementation
with one hidden layer

File: Network.cpp
*****************************************
*/

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Network.h"

using namespace std;

Network::Network(vector<Node *> i, vector<Node *> h, vector<Node *> o) {
	inputLayer = i;
	hiddenLayer = h;
	outputLayer = o;
}

void Network::Train(string fileName, int epochs, double learningRate) {

	// Get training data parameters
	ifstream trainFile(fileName);
	int numExamples, numInputs, numOutputs;
	trainFile >> numExamples >> numInputs >> numOutputs;

	// Main loop
	for (int num = 0; num < epochs; ++num) {

		// Cycle through all examples
		for (int i = 0; i < numExamples; ++i) {

			// Set all activations in input layer equal to example (skip fixed input node)
			for (int j = 1; j < numInputs + 1; ++j) {
				double x;
				trainFile >> x;
				inputLayer[j]->activation = x;
			}
			
			// Propagate inputs forward to hidden layer (skip fixed hidden node)
			for (unsigned int j = 1; j < hiddenLayer.size(); ++j) {
				// Compute new in for this node
				hiddenLayer[j]->in = 0;
				for (unsigned int k = 0; k < hiddenLayer[j]->weights.size(); ++k) {
					hiddenLayer[j]->in += (hiddenLayer[j]->weights[k] * inputLayer[k]->activation);
				}
				// Set new activation
				hiddenLayer[j]->activation = sigmoid(hiddenLayer[j]->in);
			}

			// Propagate hidden nodes forward to output layer
			for (unsigned int j = 0; j < outputLayer.size(); ++j) {
				// Compute new in for this node
				outputLayer[j]->in = 0;
				for (unsigned int k = 0; k < outputLayer[j]->weights.size(); ++k) {
					outputLayer[j]->in += (outputLayer[j]->weights[k] * hiddenLayer[k]->activation);
				}
				// Set new activation
				outputLayer[j]->activation = sigmoid(outputLayer[j]->in);
			}

			// Back propagate errors from output layer to input layer

			// Calculate errors at the output layer
			for (unsigned int j = 0; j < outputLayer.size(); ++j) {
				double desired;
				trainFile >> desired;
				outputLayer[j]->error = sigmoidPrime(outputLayer[j]->in) * (desired - outputLayer[j]->activation);
			}

			// Calculate errors at the hidden layer (skip fixed node)
			for (unsigned int j = 1; j < hiddenLayer.size(); ++j) {
				hiddenLayer[j]->error = 0;
				for (unsigned int k = 0; k < outputLayer.size(); ++k) {
					hiddenLayer[j]->error += (outputLayer[k]->weights[j] * outputLayer[k]->error);
				}
				hiddenLayer[j]->error *= sigmoidPrime(hiddenLayer[j]->in);
			}

			// Update output node weights
			for (unsigned int j = 0; j < outputLayer.size(); ++j) {
				for (unsigned int k = 0; k < outputLayer[j]->weights.size(); ++k) {
					outputLayer[j]->weights[k] += (learningRate * hiddenLayer[k]->activation * outputLayer[j]->activation);
				}
			}

			// Update hidden node weights
			for (unsigned int j = 1; j < hiddenLayer.size(); ++j) {
				for (unsigned int k = 0; k < hiddenLayer[j]->weights.size(); ++k) {
					hiddenLayer[j]->weights[k] += (learningRate * inputLayer[k]->activation * hiddenLayer[j]->activation);
				}
			}

		}

	}

	trainFile.close();
}

Network Network::LoadFromFile(string fileName) {
	/*
	 * Load initial data from file
	 */

	ifstream initFile(fileName);

	// Get number of nodes in each layer
	int numInputs, numHidden, numOutputs;
	initFile >> numInputs >> numHidden >> numOutputs;

	// Initialize all layers
	vector<Node *> inputs, hiddens, outputs;
	inputs.resize(numInputs + 1);
	hiddens.resize(numHidden + 1);
	outputs.resize(numOutputs);

	// Initialize input nodes
	Node * inputFixed = new Node();
	inputFixed->activation = -1;
	inputs[0] = inputFixed;
	for (int i = 1; i < numInputs + 1; ++i) {
		Node * n = new Node();
		inputs[i] = n;
	}

	// Initialize hidden nodes
	Node * hiddenFixed = new Node();
	hiddenFixed->activation = -1;
	hiddens[0] = hiddenFixed;
	for (int i = 1; i < numHidden + 1; ++i) {
		Node * n = new Node();
		vector<double> weights;
		for (int j = 0; j < numInputs + 1; ++j) {
			double w;
			initFile >> w;
			weights.push_back(w);
		}
		hiddens[i] = n;
		hiddens[i]->weights = weights;
	}

	// Initialize output nodes
	for (int i = 0; i < numOutputs; ++i) {
		Node * n = new Node();
		vector<double> weights;
		for (int j = 0; j < numHidden + 1; ++j) {
			double w;
			initFile >> w;
			weights.push_back(w);
		}
		outputs[i] = n;
		outputs[i]->weights = weights;
	}

	initFile.close();

	return Network(inputs, hiddens, outputs);
}

void Network::SaveToFile(string fileName, Network n) {
	ofstream saveFile(fileName);

	// Write numbers of nodes to first line
	saveFile << n.inputLayer.size() - 1 << " " << n.hiddenLayer.size() - 1 << " " << n.outputLayer.size() << "\n";

	// Set double precision
	saveFile << fixed << std::setprecision(3);

	// Write weights of hidden layers to next lines (skip fixed node)
	for (unsigned int i = 1; i < n.hiddenLayer.size(); ++i) {
		for (unsigned int j = 0; j < n.hiddenLayer[i]->weights.size(); ++j) {
			saveFile << n.hiddenLayer[i]->weights[j];
			if (j != n.hiddenLayer[i]->weights.size() - 1) {
				saveFile << " ";
			}
		}
		saveFile << "\n";
	}

	// Write weights of output layers to next lines
	for (unsigned int i = 0; i < n.outputLayer.size(); ++i) {
		for (unsigned int j = 0; j < n.outputLayer[i]->weights.size(); ++j) {
			saveFile << n.outputLayer[i]->weights[j];
			if (j != n.outputLayer[i]->weights.size() - 1) {
				saveFile << " ";
			}
		}
		saveFile << "\n";
	}

	saveFile.close();
}

double Network::sigmoid(double num) {
	return (double)1 / ((double)1 + exp(-num));
}

double Network::sigmoidPrime(double num) {
	return sigmoid(num) * ((double)1 - sigmoid(num));
}
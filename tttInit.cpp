/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural network implementation
with one hidden layer

File: tttInit.cpp
Description: Initializes a neural network
with 9 inputs, 1 output (tic tac toe
spec) and a modifiable number of hidden
nodes
*****************************************
*/

#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {

	srand(time(NULL));

	ofstream outFile("ttt.init");

	int numInputs = 9, numOutputs = 1;
	int numHidden;
	cout << "Enter the number of nodes in the hidden layer: ";
	cin >> numHidden;

	outFile << numInputs << " " << numHidden << " " << numOutputs << endl;

	// Generate random weights
	for (int i = 0; i < numHidden; ++i) {
		for (int j = 0; j < numInputs + 1; ++j) {
			double w = ((double) rand() / (RAND_MAX));
			outFile.precision(3);
			outFile << fixed << w;
			if (j != numInputs) {
				outFile << " ";
			}
		}
		outFile << endl;
	}
	for (int i = 0; i < numOutputs; ++i) {
		for (int j = 0; j < numHidden + 1; ++j) {
			double w = ((double) rand() / (RAND_MAX));
			outFile.precision(3);
			outFile << fixed << w;
			if (j != numHidden) {
				outFile << " ";
			}
		}
		outFile << endl;
	}

	outFile.close();

	return 0;
}
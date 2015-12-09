/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural network implementation
with one hidden layer

File: train.cpp
Description: Trains a neural network on
a given training set and outputs the
trained network into a specified file
*****************************************
*/

#include <iostream>
#include <string>
#include <limits>
#include "Network.h"

using namespace std;

int main() {

	// Get filenames
	string initFileName;
	cout << "Enter the name of a neural net file: ";
	cin >> initFileName;

	string trainingFileName;
	cout << "Enter the name of a training set file: ";
	cin >> trainingFileName;

	string outputFileName;
	cout << "Enter the name of an output file: ";
	cin >> outputFileName;

	// Get training parameters

	int epochs;
	cout << "Enter the number of epochs: ";
	while (!(cin >> epochs) || epochs <= 0) {
		// Ensure integral input
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		continue;
	}

	double learningRate;
	cout << "Enter the learning rate: ";
	while (!(cin >> learningRate) || learningRate < 0) {
		// Ensure valid input
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	Network network = Network::LoadFromFile(initFileName); // Create and initialize network
	cout << "Network initialized successfully" << endl;

	network.Train(trainingFileName, epochs, learningRate); // Train network
	cout << "Network trained successfully" << endl;

	Network::SaveToFile(outputFileName, network); // Save network
	cout << "Network saved successfully" << endl;

	return 0;
}
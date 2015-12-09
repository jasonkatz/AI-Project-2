/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural network implementation
with one hidden layer

File: test.cpp
Description: Tests a neural network's
performance on a testing set and outputs
results into a specified file
*****************************************
*/

#include <iostream>
#include <string>
#include "Network.h"

using namespace std;

int main() {

	// Get filenames
	string initFileName;
	cout << "Enter the name of a neural net file: ";
	cin >> initFileName;

	string testingFileName;
	cout << "Enter the name of a testing set file: ";
	cin >> testingFileName;

	string outputFileName;
	cout << "Enter the name of an output file: ";
	cin >> outputFileName;

	Network n = Network::LoadFromFile(initFileName); // Create and initialize network
	cout << "Network initialized successfully" << endl;

	n.Test(testingFileName, outputFileName); // Test and save network
	cout << "Network tested and saved successfully" << endl;

	return 0;
}
/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural Network implementation
with one hidden layer

File: train.cpp
*****************************************
*/

#include <iostream>
#include "Network.h"

using namespace std;

int main() {

	Network n = Network::LoadFromFile("sample.NNGrades.init");
	n.Train("grades.train", 100, .05);
	Network::SaveToFile("out.txt", n);

	//system("pause");
	return 0;
}
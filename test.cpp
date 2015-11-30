/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural Network implementation
with one hidden layer

File: test.cpp
*****************************************
*/

#include <iostream>
#include "Network.h"

using namespace std;

int main() {

	Network n = Network::LoadFromFile("trained.txt");
	n.Test("grades.test", "results.txt");

	return 0;
}
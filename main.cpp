/*
*****************************************
Jason Katz
ECE-469 Project 2: Neural Network

Neural Network implementation
with one hidden layer

File: main.cpp
*****************************************
*/

#include <iostream>
#include "Network.h"

using namespace std;

int main() {

	Network n = Network::LoadFromFile("sample.NNWDBC.init");
	n.Train("wdbc.train", 100, .1);
	Network::SaveToFile("out.txt", n);

	//system("pause");
	return 0;
}
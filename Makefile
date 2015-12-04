train:
	g++ -std=c++11 train.cpp Network.cpp

test:
	g++ -std=c++11 test.cpp Network.cpp

parse:
	g++ -std=c++11 connect4Parse.cpp

init:
	g++ -std=c++11 connect4Init.cpp

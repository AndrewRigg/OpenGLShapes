#pragma once

#include <math.h>

class Node{

public:
	Node();
	~Node();
	Node(int x, int y);

	int f;
	int g;
	char attribute;
	//void checkNext(Node squares[gridSize][gridSize]);
	void checkNext(Node squares[20][20]);
	void moveToNext(Node goal);
	bool isPassable();
	//This is f(n) the total cost function
	float calculatePathCost(Node node, Node goal);
	//This is h(n) the heuristic function
	float straightLineDistance(Node goal);
	//This is g(n) the actual cost function
	float manhattanDistance(Node node);
	int x;
	int y;
};
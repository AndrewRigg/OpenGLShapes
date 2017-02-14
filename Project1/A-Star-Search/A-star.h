#pragma once

#include <math.h>
#include "A-star.h"

class Node{

public:
	Node();
	~Node();
	Node(int x, int y);

	int f;
	char attribute;
	float g;
	
	//void checkNext(Node squares[gridSize][gridSize]);
	void updateOpenList();
	void moveToNext(Node current, Node goal);
	bool isPassable(Node n);
	Node parent(Node node);
	Node child(Node node);
	//This is f(n) the total cost function
	float calculatePathCost(Node node, Node goal);
	//This is h(n) the heuristic function
	float straightLineDistance(Node goal);
	//This is g(n) the actual cost function
	float manhattanDistance(Node node);
	bool Node::operator==(Node node);
	bool Node::operator!=(Node node);
	int x;
	int y;
};

void setUpNullList(Node squares[20][20]);
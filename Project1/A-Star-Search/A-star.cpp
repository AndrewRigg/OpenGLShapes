//A* algorithm to find optimal path for 
//f(n) = g(n) + h(n)

#include "A-star.h"
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

Node::Node() {};
Node::~Node() {}
Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
}
;

const int gridSize = 20;

vector<Node> openList;
vector<Node> closedList;

void Node::checkNext(Node squares[20][20]) {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i != 0 && j != 0) {
				Node a = squares[x + j][y + i];
				a.x = x + i;
				a.y = y + j;
				if (a.isPassable()) {
					openList.push_back(a);
				}
			}
		}
	}
}

bool Node::isPassable() {
	if (attribute = ' ') {
		return true;
	}
	else {
		return false;
	}
}

void Node::moveToNext(Node goal) {
	//for each node in the open list, try moving there and calculating the pathfinding function		
	int currentCost = 1000;
	int pushed = 0;
	for (Node &i : openList) {
		int newPathCost = calculatePathCost(i, goal);
		if (newPathCost < currentCost) {
			if (pushed > 0) {
				closedList.pop_back;
			}
			currentCost = newPathCost;
			closedList.push_back(i);
			pushed++;
		}
	}
}

float Node::calculatePathCost(Node node, Node goal) {
	//This is the function f(n) = g(n) + h(n) to be minimised to determine the best path
	return(node.straightLineDistance(goal) + manhattanDistance(node));
}

float Node::straightLineDistance(Node goal) {
	return(sqrt(float(pow((x - goal.x), 2) + pow((y - goal.y), 2))));
}

float Node::manhattanDistance(Node node) {
	return(abs(x - node.x) + abs(y - node.y));
}

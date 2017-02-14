//A* algorithm to find optimal path for 
//f(n) = g(n) + h(n)
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>
#include <iostream>

#include "A-star.h"

using namespace std;

Node::Node() {};
Node::~Node() {}
Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
}
;

bool Node::operator==(Node node) {
	return(x == node.x && y == node.y);
}

bool Node::operator!=(Node node) {
	return(x != node.x || y != node.y);
}

vector<Node> openList;
vector<Node> closedList;
vector<Node> nullList;

void setUpNullList(Node squares[20][20]) {
	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j <= 20; j++) {
			Node a = squares[j][i];
			nullList.push_back(a);
		}
	}
}

void Node::updateOpenList() {
	for (Node &i : nullList) {
		float nodeX = i.x;
		float nodeY = i.y;		
		if (*this != i && abs(x - nodeX) <= 1 && abs(y - nodeY) <= 1) {
			if (isPassable(i) && !(find(openList.begin(), openList.end(), i) != openList.end())) {
				openList.push_back(i);
			}
		}
	}
}

bool Node::isPassable(Node n) {
	if (n.attribute == ' ' || n.attribute == 'G') {
	//	cout << "\nThis: (" << n.x <<  n.y;
		return true;
	}
	else {
		return false;
	}
}

void Node::moveToNext(Node current, Node goal) {
	//for each node in the open list, try moving there and calculating the pathfinding function		
	int currentCost = calculatePathCost(*this, goal);
	int pushed = 0;
	for (Node &i : openList) {
		i.g += g + manhattanDistance(i);
		if (i.x == goal.x && i.y == goal.y) {
			i.parent(current);
			*this = i;
			closedList.push_back(i);
		}else {	
			int newPathCost = calculatePathCost(i, goal);
			if (newPathCost < currentCost) {
				if (pushed > 0) {
					closedList.pop_back();
				}
				i.parent(current);
				*this = i;
				currentCost = newPathCost;
				closedList.push_back(i);
				pushed++;
			}
			*this = closedList.at(closedList.size()-1);
		}
	}
	/*auto it = find(openList.begin(), openList.end(), this);
	if (it != openList.end())
		openList.erase(it);*/
}

Node Node::child(Node node) {
	return node;
}

Node Node::parent(Node node) {
	return node;
}

float Node::calculatePathCost(Node node, Node goal) {
	//This is the function f(n) = g(n) + h(n) to be minimised to determine the best path
	//return(node.straightLineDistance(goal) + manhattanDistance(node));
	return(node.straightLineDistance(goal) + node.g);
}

float Node::straightLineDistance(Node goal) {
	return(sqrt(float(pow((x - goal.x), 2) + pow((y - goal.y), 2))));
}

float Node::manhattanDistance(Node node) {
	return(abs(x - node.x) + abs(y - node.y));
}

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

void updateOpenList(Node current) {
	for (Node &i : nullList) {
		float nodeX = i.x;
		float nodeY = i.y;		
		if (&current != &i && abs(current.x - nodeX) <= 1 && abs(current.y - nodeY) <= 1) {
			if (isPassable(i) && !(find(openList.begin(), openList.end(), i) != openList.end())) {
				openList.push_back(i);
			}
		}
	}
}

bool isPassable(Node n) {
	if (n.attribute == ' ' || n.attribute == 'G') {
	//	cout << "\nThis: (" << n.x <<  n.y;
		return true;
	}
	else {
		return false;
	}
}

void moveToNext(Node current, Node goal) {
	//for each node in the open list, try moving there and calculating the pathfinding function		
	int currentCost = calculatePathCost(current, goal);
	int pushed = 0;
	for (Node &i : openList) {
		i.g += current.g + manhattanDistance(i);
		if (i.x == goal.x && i.y == goal.y) {
			
			current = i;
			closedList.push_back(i);
		}else {	
			int newPathCost = calculatePathCost(i, goal);
			if (newPathCost < currentCost) {
				if (pushed > 0) {
					closedList.pop_back();
				}
				
				struct Parent parent1 = { 1,2 };
				current = i;
				currentCost = newPathCost;
				closedList.push_back(i);
				pushed++;
			}
			current = closedList.at(closedList.size()-1);
		}
	}
	/*auto it = find(openList.begin(), openList.end(), this);
	if (it != openList.end())
		openList.erase(it);*/
}


float calculatePathCost(Node node, Node goal) {
	//This is the function f(n) = g(n) + h(n) to be minimised to determine the best path
	//return(node.straightLineDistance(goal) + manhattanDistance(node));
	return(node.straightLineDistance(goal) + node.g);
}

float straightLineDistance(Node goal) {
	return(sqrt(float(pow((x - goal.x), 2) + pow((y - goal.y), 2))));
}

float manhattanDistance(Node node) {
	return(abs(x - node.x) + abs(y - node.y));
}

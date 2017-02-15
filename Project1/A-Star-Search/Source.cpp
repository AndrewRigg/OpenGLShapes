//Set up conditions for search algorithm

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Node.h"

using namespace std;

//Functions


Node moveToNext(Node current, Node goal);
//This is f(n) the total cost function
float calculatePathCost(Node node, Node goal);
//This is h(n) the heuristic function
float straightLineDistance(Node current, Node goal);
//This is g(n) the actual cost function
float manhattanDistance(Node current, Node node);
void setUpNullList(Node squares[20][20]);
//void checkNext(Node squares[gridSize][gridSize]);
void updateOpenList(Node current);
void updateOpenValues(Node goal);

vector<Node> openList;
vector<Node> closedList;
vector<Node> nullList;

const int gridSize = 20;
bool running = true;
Node squares[gridSize][gridSize];
Node currentNode, endNode;


void setUpNullList(Node squares[20][20]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			Node a = squares[j][i];
			nullList.push_back(a);
		}
	}
}

void updateOpenList(Node current) {
	for (Node &i : nullList) {
		float nodeX = i.x;
		float nodeY = i.y;
		if (current != i && abs(current.x - nodeX) < 2 && abs(current.y - nodeY) < 2) {
			if (i.accessible) {
				if (std::find(openList.begin(), openList.end(), i) != openList.end())
				i.parent = { current.x, current.y };
				//here check it's not already in the list
				openList.push_back(i);
			}
		}
	}
}

void updateOpenValues(Node goal) {
	for (Node &i : openList) {
		i.f = calculatePathCost(i, goal);
	}
}

Node moveToNext(Node current, Node goal) {
	//for each node in the open list, try moving there and calculating the pathfinding function		
	int currentCost = calculatePathCost(current, goal);
	int pushed = 0;
	int first = 0;
	for (Node &i : openList) {
		if (first == 0) {
			current = i;
			i.g = current.g + manhattanDistance(i, current);
			currentCost = calculatePathCost(current, goal);
			first++;
		}
		int newPathCost = calculatePathCost(i, goal);
		if (i.x == goal.x && i.y == goal.y) {
			current = i;
			closedList.push_back(i);
		}
		else if (newPathCost < currentCost) {
				currentCost = newPathCost;
				if (pushed > 0) {
					closedList.pop_back();
					pushed--;
				}
				current = i;
				closedList.push_back(i);
				pushed++;
		}
	}
	//remove i from openList
	for (std::vector<Node>::iterator iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if (*iter == current)
		{	
			openList.erase(iter);
			break;
		}
	}
	current.accessible = false;
	return current;
}

float calculatePathCost(Node node, Node goal) {
	//This is the function f(n) = g(n) + h(n) to be minimised to determine the best path
	return(straightLineDistance(node, goal) + node.g);
}

float straightLineDistance(Node current, Node goal) {
	return(sqrt(float(pow((current.x - goal.x), 2) + pow((current.y - goal.y), 2))));
}

float manhattanDistance(Node current, Node node) {
	return(abs(current.x - node.x) + abs(current.y - node.y));
}

bool areSuitableRand(int TempRand, int TempRand2) {
	srand(time(NULL));
	if (TempRand == TempRand2) {
		return false;
	}
	int startX = TempRand % 20;
	int startY = (TempRand % 400)/20;
	int endX = TempRand2 % 20;
	int endY = (TempRand2 % 400) / 20;
	return (startX != endX || startY != endY);
}

void printMaze(Node squares [20][20], int count, int startX, int startY, int endX, int endY) {
	cout << ("\t _______________________________________________________________________________\n");

	for (int i = 0; i < gridSize; i++) {
		cout << "\t";
		for (int j = 0; j < gridSize; j++) {
			if (endX == j && endY == i) {
				if (squares[j][i].attribute = 'X') {
					count--;
				}
				squares[j][i].attribute = 'G';
				squares[j][i].accessible = true;
			}
			else if (startX == j && startY == i) {
				if (squares[j][i].attribute = 'X') {
					count--;
				}
				squares[j][i].attribute = 'S';
				squares[j][i].accessible = true;
			}
			cout << "| ";
			cout << (squares[j][i].attribute);
			cout << " ";
		}
		cout << ("| \n\t _______________________________________________________________________________\n");
	}
}

int main() {
	srand(time(NULL));
	cout << ("\n\tA* Pathfinding Algorithm\n\n\tRandomly Assigned Maze: \n");
	int count = 0;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			Node a = Node(j,i);
			a.f = 0;
			a.g = 0;
			a.h = 0;
			squares[j][i] = a;
			int TempRand = rand()%100;
			if (TempRand > 75) {
				squares[j][i].attribute = 'X';
				squares[j][i].accessible = false;
				count++;
			}
			else {
				squares[j][i].attribute = ' ';
			}
		}
	}

	int startX = rand() % 20;
	int startY = (rand() % 400) / 20;
	int endX = rand() % 20;
	int endY = (rand() % 400) / 20;
	while (startX == endX && startY == endY) {
		startX = rand() % 20;
		startY = (rand() % 400) / 20;
		endX = rand() % 20;
		endY = (rand() % 400) / 20;
	}

	printMaze(squares, count, startX, startY, endX, endY);

	currentNode = squares[startX][startY];
	currentNode.g = 0;
	endNode = squares[endX][endY];
	cout << "\n\tImpassable blocks: " << count << " \n\tCoordinates of Start: (" << startX << " , " << startY << ") \n\tCoordinates of End: (" << endX << " , " << endY << ")\n\n";
	cout << "\tStraight Line Distance To Goal: " << straightLineDistance(currentNode, endNode);
	cout << "\n\tManhattan Distance To Goal: " << manhattanDistance(currentNode,endNode) << "\n";
	
	
	int steps = 0;
	setUpNullList(squares);
	do{
		//run A* algorithms to find the quickest path
		if (currentNode.x == endX && currentNode.y == endY) {
			cout << "\n\n\tREACHED YOUR GOAL!";
			running = false;
		}else if (steps > 1000) {
			cout << "\n\t---------- TOO MANY STEPS -----------";
			running = false;
		}
		else {
			steps++;
			cout << "\n\tMoved from: (" << currentNode.x << ", " << currentNode.y << ")\tto (";
			updateOpenList(currentNode);
			//updateOpenValues(endNode);
			currentNode = moveToNext(currentNode, endNode);
			cout << currentNode.x << ", " << currentNode.y << ")";
			cout << "\tDistance to goal: " << straightLineDistance(currentNode, endNode);
		}
	} while (running);

	Sleep(500000);
	return 0;

}
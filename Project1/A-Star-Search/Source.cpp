//Set up conditions for search algorithm
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include<time.h>
#include"A-star.h"
#include <vector>

using namespace std;

//Functions

//Variables
const int gridSize = 20;
Node squares[gridSize][gridSize];
bool		running = true;
Node currentNode, endNode;

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

int main() {
	srand(time(NULL));
	cout << ("\n\tA* Pathfinding Algorithm\n\n\tRandomly Assigned Maze: \n");
	int count = 0;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			Node a = Node(j,i);
			squares[j][i] = a;
			int TempRand = rand()%100;
			if (TempRand > 75) {
				squares[j][i].attribute = 'X';
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
	cout << ("\t _______________________________________________________________________________\n");

	for (int i = 0; i < gridSize; i++) {	
		cout << "\t";
		for (int j = 0; j < gridSize; j++) {
			if (endX == j && endY == i) {
				if (squares[j][i].attribute = 'X') {
					count--;
				}
				squares[j][i].attribute = 'G';
			}
			else if (startX == j && startY == i) {
				if (squares[j][i].attribute = 'X') {
					count--;
				}
				squares[j][i].attribute = 'S';
			}
			cout << "| ";
			cout << (squares[j][i].attribute);
			cout << " ";
		}
		cout << ("| \n\t _______________________________________________________________________________\n");
	}
	cout << "\n\tImpassable blocks: " << count << " \n\tCoordinates of Start: (" << startX << " , " << startY << ") \n\tCoordinates of End: (" << endX << " , " << endY << ")\n\n";
	cout << "\tStraight Line Distance To Goal: " << squares[startX][startY].straightLineDistance(squares[endX][endY]);
	cout << "\n\tManhattan Distance To Goal: " << squares[startX][startY].manhattanDistance(squares[endX][endY]) << "\n";
	
	currentNode = squares[startX][startY];
	endNode = squares[endX][endY];
	int steps = 0;
	do{
		//run A* algorithms to find the quickest path
		if (currentNode.x == endX && currentNode.y == endY) {
			cout << "\n\n\tREACHED YOUR GOAL!";
			running = false;
		}else if (steps > 50) {
			cout << "\n\t---------- TOO MANY STEPS -----------";
			running = false;
		}
		else {
			steps++;
			cout << "\n\tMoved from: (" << currentNode.x << ", " << currentNode.y << ")\tto (";
			currentNode.checkNext(squares);
			currentNode.moveToNext(endNode);
			cout << currentNode.x << ", " << currentNode.y << ")";
			cout << "\tDistance to goal: " << currentNode.straightLineDistance(endNode);
		}
	} while (running);

	Sleep(500000);
	return 0;

}
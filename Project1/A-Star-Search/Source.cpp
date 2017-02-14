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
			squares[j][i] = Node(j, i);
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
	cout << "\n\tManhattan Distance To Goal: " << squares[startX][startY].manhattanDistance(squares[endX][endY]);
	
	currentNode = squares[startX][startY];
	endNode = squares[endX][endY];
	do{
		//run A* algorithms to find the quickest path
		if (currentNode.x == endX && currentNode.y == endY) {
			running = false;
		}
		cout << "\n\n\tMoved from: (" << currentNode.x << ", " << currentNode.y << ") to (";
		currentNode.checkNext(squares);
		currentNode.moveToNext(endNode);
		cout << currentNode.x << ", " << currentNode.y << ")";
		running = false;
	} while (running);

	Sleep(50000);
	return 0;

}
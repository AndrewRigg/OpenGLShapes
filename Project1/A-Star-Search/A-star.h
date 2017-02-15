#pragma once
#include <math.h>
#include "A-star.h"
#include "Node.h"

using namespace std;

void moveToNext(Node current, Node goal);
//This is f(n) the total cost function
float calculatePathCost(Node node, Node goal);
//This is h(n) the heuristic function
float straightLineDistance(Node goal);
//This is g(n) the actual cost function
float manhattanDistance(Node node);
void setUpNullList(Node squares[20][20]);
//void checkNext(Node squares[gridSize][gridSize]);
void updateOpenList(Node current);
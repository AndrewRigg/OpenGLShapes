////A* algorithm to find optimal path for 
////f(n) = g(n) + h(n)
//#include <stdlib.h>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include "Node.h"
//
//using namespace std;
//
//void moveToNext(Node current, Node goal);
////This is f(n) the total cost function
//float calculatePathCost(Node node, Node goal);
////This is h(n) the heuristic function
//float straightLineDistance(Node current, Node goal);
////This is g(n) the actual cost function
//float manhattanDistance(Node current, Node node);
//void setUpNullList(Node squares[20][20]);
////void checkNext(Node squares[gridSize][gridSize]);
//void updateOpenList(Node current);
//
//vector<Node> openList;
//vector<Node> closedList;
//vector<Node> nullList;
//
//
//void setUpNullList(Node squares[20][20]) {
//	for (int i = 0; i <= 20; i++) {
//		for (int j = 0; j <= 20; j++) {
//			Node a = squares[j][i];
//			nullList.push_back(a);
//		}
//	}
//}
//
//void updateOpenList(Node current) {
//	for (Node &i : nullList) {
//		float nodeX = i.x;
//		float nodeY = i.y;		
//		if (&current != &i && abs(current.x - nodeX) <= 1 && abs(current.y - nodeY) <= 1) {
//			if (i.accessible) {
//				//here check it's not already in the list
//				openList.push_back(i);
//			}
//		}
//	}
//}
//
//void moveToNext(Node current, Node goal) {
//	//for each node in the open list, try moving there and calculating the pathfinding function		
//	int currentCost = calculatePathCost(current, goal);
//	int pushed = 0;
//	for (Node &i : openList) {
//		i.g += current.g + manhattanDistance(i, goal);
//		if (i.x == goal.x && i.y == goal.y) {
//			current = i;
//			closedList.push_back(i);
//		}else {	
//			int newPathCost = calculatePathCost(i, goal);
//			if (newPathCost < currentCost) {
//				if (pushed > 0) {
//					closedList.pop_back();
//				}
//				i.parent = {current.x, current.y};
//				current = i;
//				currentCost = newPathCost;
//				closedList.push_back(i);
//				pushed++;
//			}
//			current = closedList.at(closedList.size()-1);
//		}
//	}
//}
//
//float calculatePathCost(Node node, Node goal) {
//	//This is the function f(n) = g(n) + h(n) to be minimised to determine the best path
//	return(straightLineDistance(node, goal) + node.g);
//}
//
//float straightLineDistance(Node current, Node goal) {
//	return(sqrt(float(pow((current.x - goal.x), 2) + pow((current.y - goal.y), 2))));
//}
//
//float manhattanDistance(Node current, Node node) {
//	return(abs(current.x - node.x) + abs(current.y - node.y));
//}

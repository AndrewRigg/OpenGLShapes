#pragma once

#include <math.h>
#include "A-star.h"

class Node {

public:
	Node();
	~Node();
	Node(int x, int y);

	float f;	
	float g;
	float h;
	bool accessible;
	char attribute;
	//struct Parent {};
	struct Parent {
		int xCoord;
		int yCoord;
	}parent;
	int x;
	int y;
};

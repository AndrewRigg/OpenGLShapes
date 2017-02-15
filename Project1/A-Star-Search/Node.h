#pragma once

#include <math.h>

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

	struct Parent {
		int xCoord;
		int yCoord;
	}parent;

	bool Node::operator==(Node vec);
	bool Node::operator!=(Node vec);
	int x;
	int y;
};

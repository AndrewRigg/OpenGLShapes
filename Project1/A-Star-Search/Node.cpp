#include "Node.h"

using namespace std;

Node::Node() {};
Node::~Node() {}
Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
}
;

struct Parent {
	int xCoord;
	int yCoord;
}parent;
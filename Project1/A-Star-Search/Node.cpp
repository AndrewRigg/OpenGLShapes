#include "Node.h"

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
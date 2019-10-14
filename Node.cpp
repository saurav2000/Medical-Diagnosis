#include "Node.h"
using namespace std;

Node::Node(int k)
{
	index = k;
}

void Node::addParent(int x)
{
	parents.push_back(x);
}

void Node::initTable(int x)
{
	table.reserve(x);
	for(int i=0;i<x;++i)
		table.push_back(-1);
}

void Node::addValue(string s)
{
	values.push_back(s);
}

void Node::initTable(std::vector<float> x)
{
	table = x;
}

void Node::changeTable(int x, float f)
{
	table[x] = f;
}
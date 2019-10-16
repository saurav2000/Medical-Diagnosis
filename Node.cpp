#include "Node.h"
using namespace std;

Node::Node(int k)
{
	index = k;
	valueCNT = 0;
}

void Node::addParent(Node *x)
{
	parents.push_back(x);
}

void Node::initTable(int x)
{
	table.reserve(x);
	for(int i=0;i<x;++i)
		table.push_back(0);
}

void Node::addValue(string s)
{
	values[s] = valueCNT++;
}

void Node::changeTable(int x, float f)
{
	table[x] = f;
}

void Node::dealWith(vector<string> s)
{
	for(int i=0;i<s.size();++i)
	{
		
	}
}

void Node::makeSizes()
{
	int pro = 1;
	sizes.push_back(1);
	for(int i=parents.size()-1;i>=0;--i)
	{
		pro*= parents[i]->valueCNT;
		sizes.push_back(pro);
	}
	
	reverse(sizes.begin(), sizes.end());
}
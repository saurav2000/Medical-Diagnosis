#include "Node.h"
using namespace std;

float ALPHA = 0.1;

Node::Node(int k)
{
	index = k;
	valueCount = 0;
}

void Node::addParent(Node *n)
{
	parents.push_back(n);
	n->addChild(this);
}

void Node::addChild(Node *n)
{
	children.push_back(n);
}

void Node::initTables(int x)
{
	initObserveCount.reserve(x);
	observeCount.reserve(x);
	CPT.reserve(x);
	for(int i=0;i<x;++i)
	{
		observeCount.push_back(0);
		CPT.push_back(0);
		initObserveCount.push_back(0);
	}
}

void Node::initCPT()
{
	observeCount = initObserveCount;
	this->evalCPT();
}

void Node::evalCPT()
{
	int s = sizes[0], n = CPT.size();
	float sum[s] = {0.0}, alpha = 0;
	
	for(int i=0;i<n;++i)
	{
		if(observeCount[i]==0)
		{
			alpha = ALPHA;
			break;
		}
	}

	cout<<"\n"<<index<<"\n";
	for(int i=0;i<n;++i)
	{
		observeCount[i]+=alpha;
		cout<<observeCount[i]<<"\n";
		sum[i%s]+=observeCount[i];
	}
	for(int i=0;i<n;++i)
		CPT[i] = observeCount[i] / sum[i%s];
	
	observeCount = initObserveCount;
}

void Node::addValue(string s)
{
	values[s] = valueCount++;
}

void Node::initObserveTable(vector<string> s)
{
	for(int i=0;i<s.size();++i)
	{
		if(s[i] == "\"?\"")
			return;
	}

	int res = values[s[0]]*sizes[0];
	for(int i=1;i<=parents.size();++i)
		res+= parents[i-1]->values[s[i]]*sizes[i];
	initObserveCount[res]+=1;
}

void Node::addUnknownObserve(vector<string> &s, int unknown)
{
	int res = 0, sizei = -1;
	if(unknown != index)
		res = values[s[index]]*sizes[0];
	else
		sizei = 0;
	for(int i=1;i<=parents.size();++i)
	{
		if(unknown!=parents[i-1]->index)
			res+= parents[i-1]->values[s[parents[i-1]->index]]*sizes[i];
		else
			sizei = i;
	}

	int val = (sizei==0)?valueCount:parents[sizei-1]->valueCount;
	for(int i=0;i<val;++i)
	{
		int temp = res+sizes[sizei]*i;
		observeCount[temp]+= CPT[temp];
	}
}

void Node::makeSizes()
{
	int pro = 1;
	sizes.push_back(1);
	for(int i=parents.size()-1;i>=0;--i)
	{
		pro*= parents[i]->valueCount;
		sizes.push_back(pro);
	}
	
	reverse(sizes.begin(), sizes.end());
}
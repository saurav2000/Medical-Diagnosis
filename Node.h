#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

class Node
{
	public:
	int index, valueCount;
	std::vector<Node*> parents, children;
	std::map<std::string, int> values;
	std::vector<float> observeCount, initObserveCount, CPT;
	std::vector<int> sizes;

	Node(int k);
	void addParent(Node *n);
	void addChild(Node *n);
	void initTables(int x);
	void initCPT();
	void evalCPT();
	void addValue(std::string s);
	void initObserveTable(std::vector<std::string> s);
	void makeSizes();
	void addUnknownObserve(std::vector<std::string> &s, int unknown);
};
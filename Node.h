#include <vector>
#include <string>
#include <map>
#include <algorithm>

class Node
{
	public:
	int index;
	int valueCNT;
	std::vector<Node*> parents;
	std::map<std::string, int> values;
	std::vector<float> table;
	std::vector<int> sizes;

	Node(int k);
	void addParent(Node *n);
	void initTable(int x);
	void addValue(std::string s);
	void changeTable(int x, float f);
	void dealWith(std::vector<std::string> s);
	void makeSizes();
};
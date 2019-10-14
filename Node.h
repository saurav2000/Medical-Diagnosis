#include <vector>
#include <string>

class Node
{
	public:
	int index;
	std::vector<int> parents;
	std::vector<std::string> values;
	std::vector<float> table;

	Node(int k);
	void addParent(int x);
	void initTable(int x);
	void addValue(std::string s);
	void initTable(std::vector<float> x);
	void changeTable(int x, float f);
};
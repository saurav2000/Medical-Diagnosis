#include <vector>
#include "Data.h"

class Node
{
	public:
	int index;
	std::vector<int> parents;
	std::vector<float> table;
	Data *data;

	Node(int k, Data *d);
	void addParent(int x);
	void initTable(int x);
	void initTable(std::vector<float> x);
	void changeTable(int x, float f);
};
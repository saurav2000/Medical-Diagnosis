#include <map>
#include <string>

class Data
{
	public:

	std::map<std::string, int> index;
	std::map<int, int> size;
	int i;
	Data();
	int addVar(std::string s, int k);
};
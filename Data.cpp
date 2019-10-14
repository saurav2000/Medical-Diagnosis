#include "Data.h"
using namespace std;

Data::Data()
{
	i = 0;
}

int Data::addVar(string s, int k)
{
	index.insert({s, i});
	size.insert({i, k});
	return i++;
}
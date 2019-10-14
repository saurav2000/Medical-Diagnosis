#include "Data.h"
using namespace std;

Data::Data()
{
	i = 0;
}

void Data::addVar(string s, int k)
{
	index.insert({s, i});
	size.insert({i, k});
	++i;
}
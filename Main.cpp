#include "Node.h"
#include "Data.h"
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin;
ofstream fout;
vector<Node*> nodes;
Data *data;
char *output_name;

int parse(char *file_name)
{
	fin.open(file_name);

	while(!fin.eof())
	{
		string s;
		fin>>s;
		if(s[0]=='v')
		{
			string var;
			fin>>var;
			while(s[0]!='d')
				fin>>s;
			int nVar = stoi(s.substr(9, s.size()-10));
			fin>>s;
			Node *node = new Node(data->addVar(var, nVar));
			for(int i=0;i<nVar;++i)
			{
				fin>>s;
				node->addValue(s);
			}
			for(int i=0;i<8;++i)
				fin>>s;
			nodes.push_back(node);
		}
		else if(s[0]=='p')
		{
			fin>>s;
			vector<string> temp;
			while(s[0]!=')')
			{
				fin>>s;
				temp.push_back(s);
			}
			Node *node = nodes[data->index[temp[0]]];
			for(int i=1;i<temp.size()-1;++i)
				node->addParent(nodes[data->index[temp[i]]]);
			for(int i=0;i<5;++i)
				fin>>s;
			node->initTable(stoi(s));
			for(int i=0;i<5;++i)
				getline(fin, s);
		}
		else if(s[0]=='n')
		{
			for(int i=0;i<9;++i)
				fin>>s;
		}
		else if(s[0]=='/'&&s[1]=='/')
			getline(fin, s);
	}

	for(int i=0;i<nodes.size();++i)
		nodes[i] -> makeSizes();

	fin.close();
	return 404;
}

int learn(char *file_name)
{
	int n = nodes.size();
	fin.open(file_name);
	vector<vector<string> > data;
	map<int, int> unknown;
	data.reserve(12000);
	int cnt = 0;
	while(!fin.eof())
	{
		vector<string> temp(n);
		for(int i=0;i<n;++i)
		{
			fin>>temp[i];
			if(temp[i] == "?")
				unknown[cnt] = i;
		}
		
		++cnt;
		data.push_back(temp);
	}

	for(int j=0;j<data.size();++j)
	{
		for(int i=0;i<n;++i)
		{
			vector<string> v;
			v.push_back(data[j][i]);
			for(int j=0;j<nodes[i]->parents.size();++j)
				v.push_back(data[j][nodes[i]->parents[j]->index]);
			nodes[i]->dealWith(v);	
		}
	}

	fin.close();
	return 405;
}

int output()
{
	fout.open(output_name);
	fout.close();
	return 406;
}

int main(int argc, char **argv)
{
	output_name = argv[3];
	data = new Data();
	cout<<parse(argv[1])<<"\n";
	cout<<learn(argv[2])<<"\n";
	cout<<output()<<"\n";
}

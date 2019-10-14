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
				node->addValue(s.substr(1, s.size()-2));
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
				temp.push_back(s.substr(1, s.size()-2));
			}
			Node *node = nodes[data->index[temp[0]]];
			for(int i=1;i<temp.size()-1;++i)
				node->addParent(data->index[temp[i]]);
			for(int i=0;i<5;++i)
				fin>>s;
			node->initTable(stoi(s));
			getline(fin, s);
			getline(fin, s);
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

	fin.close();
	return 404;
}

int learn(char *file_name)
{
	fin.open(file_name);



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

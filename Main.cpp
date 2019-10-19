#include "Node.h"
#include "Data.h"
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin;
vector<Node*> nodes;
Data *data;
char *input_name;
vector<vector<string> > records;
int SWEEP_IT;

void parse()
{
	fin.open(input_name);

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
			node->initTables(stoi(s));
			for(int i=0;i<3;++i)
				getline(fin, s);
		}

		else if(s[0]=='n')
		{
			for(int i=0;i<2;++i)
				getline(fin, s);
		}
		else if(s[0]=='/'&&s[1]=='/')
			getline(fin, s);
	}

	for(int i=0;i<nodes.size();++i)
		nodes[i]->makeSizes();

	fin.close();
}

void learn(char *file_name)
{
	int n = nodes.size();
	fin.open(file_name);
	map<int, int> questionMark;
	records.reserve(12000);
	int cnt = 0;

	//DATA FILE READ
	while(!fin.eof())
	{
		vector<string> temp(n);
		for(int i=0;i<n;++i)
		{
			fin>>temp[i];
			if(temp[i] == "\"?\"")
				questionMark[cnt] = i;
		}
		
		++cnt;
		records.push_back(temp);
	}
	fin.close();

	//IGNORING QUESTION MARKS
	for(int k=0;k<records.size();++k)
	{
		for(int i=0;i<n;++i)
		{
			vector<string> v;
			v.push_back(records[k][i]);
			for(int j=0;j<nodes[i]->parents.size();++j)
				v.push_back(records[k][nodes[i]->parents[j]->index]);
			nodes[i]->initObserveTable(v);
		}
	}

	//SEEING WHICH QUESTION MARK AFFECTS WHICH NODE
	map<int, vector<int>* > unknown;
	for(auto it = questionMark.begin(); it!=questionMark.end();++it)
	{
		vector<int> *v = new vector<int>(nodes[it->second]->children.size()+1, it->second);
		for(int i=1;i<v->size();++i)
			(*v)[i] = nodes[it->second]->children[i-1]->index;
		unknown[it->first] = v;
	}

	for(int i=0;i<n;++i)
		nodes[i]->initCPT();


	for(int k=0;k<SWEEP_IT;++k)
	{
		for(auto it = unknown.begin(); it!=unknown.end();++it)
		{
			vector<int> *v = it->second;
			for(int i=0;i<v->size();++i)
				nodes[(*v)[i]]->addUnknownObserve(records[it->first], questionMark[it->first]);
			
			for(int i=0;i<v->size();++i)
				nodes[(*v)[i]]->evalCPT(0.1);
		}
		for(int i=0;i<n;++i)
			nodes[i]->observeCount = nodes[i]->initObserveCount;
	}
}

void output()
{
	fin.open(input_name);
	string s;
	int sum = 0;
	while(!fin.eof())
	{
		getline(fin,s);
		if(s=="") continue;
		if(s[0]=='p')
		{
			printf("%s\n\ttable ", s.c_str());
			int n1 = s.find("\"");
			int n2 = s.find("\"", n1+1);
			string temp = s.substr(n1, n2-n1+1);
			Node *n = nodes[data->index[temp]];
			for(int i=0;i<n->CPT.size();++i)
				printf("%f ", n->CPT[i]);
			sum+=n->CPT.size();
			printf(";\n");
			getline(fin,s);
		}
		else
			printf("%s\n", s.c_str());
	}
	// cout<<sum<<"\n";
	fin.close();
}

int main(int argc, char **argv)
{
	//REMOVE 404 405 and 406 at the end
	input_name = argv[1];
	SWEEP_IT = stoi(argv[3]);
	data = new Data();
	parse();
	learn(argv[2]);
	output();
}

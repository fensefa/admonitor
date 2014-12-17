#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <json/json.h>
#include "jsoncompute.h"
using namespace std;

void getRule(string, Json::Value&);
	
int main(int argc, char **argv)
{
	Json::Value root;
	Json::Value rule;
	Json::Reader reader;
	Json::FastWriter writer;
	string line;
	

	string suffix[10] = {"m0","m1","m2","m6","m12","h1","h2","h6","h12","d1"};
	for(int i=1;i<argc;i++)
	{
		getRule(argv[i],rule);
	}
	
	for(int i=0;i<10;i++)
	{
		Json::Value composite;
		Json::Value data;
		//ofstream output(("composite" + suffix[i] + ".txt").c_str());

		for(int j=1;j<argc;j++)
		{
			string module = argv[j];
			ifstream input((module + suffix[i] + ".txt").c_str());
			int k = 0;
			while(getline(input,line))
			{
				reader.parse(line,root);
				data[module][k] = root;
				k++;
			}
		}
		
		
		for(int j=0;j<rule.size();j++)
		{
			string module   = rule[j]["module"].asString();
			string kpiname  = rule[j]["kpi_name"].asString();
			string module1  = rule[j]["rule"][1][0].asString();
			string kpiname1 = rule[j]["rule"][1][1].asString();
			string module2  = rule[j]["rule"][2][0].asString();
			string kpiname2 = rule[j]["rule"][2][1].asString();
			string kpiop    = rule[j]["rule"][0].asString();
			string view, view1, view2, dim, dim1, dim2;
			if(rule[j]["rule"][1].size() > 2)
			{
				view  = rule[j]["view_name"].asString();
				view1 = rule[j]["rule"][1][2].asString();
				view2 = rule[j]["rule"][2][2].asString();
			}
			if(rule[j]["rule"][1].size() > 3)
			{
				dim  = rule[j]["dim_name"].asString();
				dim1 = rule[j]["rule"][1][3].asString();
				dim2 = rule[j]["rule"][2][3].asString();
			}
			if(rule[j]["rule"][1].size() == 2)
			{

			Json::Value kpi1,kpi2,kpi3,kpis1,kpis2;

				for(int k=0;k<data[module].size();k++)
				{
					if(module2 == "CONST")
					{
						int base = atoi(kpiname2.c_str());
						data[module][k]["kpis"][kpiname] = jsonCompute(kpiop,data[module1][k]["kpis"][kpiname1],base);
					}
					else
					{
						data[module][k]["kpis"][kpiname] = jsonCompute(kpiop,data[module1][k]["kpis"][kpiname1],data[module2][k]["kpis"][kpiname2]);
					}
				}

			}
			if(rule[j]["rule"][1].size() == 3)
			{
				//to do
			}

			if(rule[j]["rule"][1].size() == 4)
			{
				for(int k=0;k<data[module].size();k++)
				{
					if(module2 == "CONST")
					{
						//to do
					}
					else
					{
						data[module][k]["kpis"][kpiname]["views"][view]["dims"][dim] = jsonCompute(kpiop,data[module1][k]["kpis"][kpiname1]["views"][view1]["dims"][dim1],data[module2][k]["kpis"][kpiname2]["views"][view2]["dims"][dim2]);
					}
				}

			}
		}
		
		for(int j=1;j<argc;j++)
		{
			string module = argv[j];
			ofstream output((module + suffix[i] + ".txt").c_str());
			for(int k=0;k<data[module].size();k++)
				output << writer.write(data[module][k]);
		}
	}
	return 0;
}

void getRule(string module, Json::Value &rule)
{
	Json::Reader reader;
	Json::Value root;
	string line;
	string filename = module + ".composite";
	ifstream input(filename.c_str());
	if(!rule.isArray())
		rule = Json::Value::null;
	while(getline(input,line))
	{
		reader.parse(line,root);
		root["module"] = module;
		rule.append(root);
	}
}

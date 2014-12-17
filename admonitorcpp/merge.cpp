#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <json/json.h>
#include <string>
#include "jsoncompute.h"
using namespace std;

/* this program is to merge data
 *
 * using like this 
 * ./a.out daytoadd 1.txt 2.txt
 *
 * */
void arrayToObject(Json::Value, string, Json::Value&);
void removeArrays(Json::Value &);

int main(int argc, char **argv)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;
	string line;
	Json::Value rootminute[1440];
	time_t t = time(NULL);
	int secondtoadd = atoi(argv[1]) * 86400;
	t += 28800;
	t = t / 86400 * 86400;
	t += secondtoadd;
	t -= 28800;
	for(int i=0;i<1440;i++)
	{
		rootminute[i]["time"] = (unsigned int)(t + 60 * i);
		rootminute[i]["time"] = rootminute[i]["time"].asString();
	}

	for(int i=3;i<argc;i++)
	{
		ifstream input(argv[i]);
		while(getline(input,line))
		{
			reader.parse(line,root);
			string x = root["time"].asString();
			unsigned int y = atoi(x.c_str());
			y += 28800;
			root["time"] = root["time"].asString();
			int z = y % 86400 / 60;
			if(z >= 0 && z < 1440)
			//rootminute[z] = jsonAdd(rootminute[z], root);
			jsonAddBy(root,rootminute[z]);
			getline(input,line);
		}
		input.close();
	}

	for(int i=0;i<1440;i++)
		removeArrays(rootminute[i]);

	string suffix[10] = {"m0","m1","m2","m6","m12","h1","h2","h6","h12","d1"};
	int length[10] = {1440,288,144,48,24,24,12,4,2,1};
	for(int i=0;i<10;i++)
	{
		string module = argv[2];
		string filename = module + suffix[i] + ".txt";
		ofstream output;
		output.open(filename.c_str());
		Json::Value *root = new Json::Value [length[i]];
		for(int j=0;j<1440;j++)
		{
			int k = j*length[i]/1440;
			//root[k] = jsonAdd(root[k], rootminute[j]);
			jsonAddBy(rootminute[j],root[k]);
		}
		for(int j=0;j<length[i];j++)
			output << writer.write(root[j]);
		output.close();
					
	}
}

void arrayToObject(Json::Value jsonArray, string keyword, Json::Value &jsonObject)
{
	jsonObject = Json::Value::null;
	if(!jsonArray.isArray())
		return;
	for(int i=0;i<jsonArray.size();i++)
	{
		string key = jsonArray[i][keyword].asString();
		jsonObject[key] = jsonArray[i];
		jsonObject[key].removeMember(keyword);
	}
}

void removeArrays(Json::Value &jsvl)
{
	
	
	for(int i=0;i<jsvl["kpis"].size();i++)
	{
		arrayToObject(jsvl["kpis"][i]["views"],"view_name",jsvl["kpis"][i]["views"]);
	}
	arrayToObject(jsvl["kpis"],"kpi_name",jsvl["kpis"]);
}

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <json/json.h>
#include <string>
#include "jsoncompute.h"
using namespace std;

int main(int argc, char **argv)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;
	string line;
	Json::Value root2;
	ifstream input("tab.txt");
	while(getline(input,line))
	{
		reader.parse(line,root);cout<<"-------------------------------\n";
		cout<<writer.write(root)<<endl;
		cout<<writer.write(root2)<<endl;
		//root2 = jsonAdd(root2,root);
		jsonAddBy(root,root2);
		cout<<writer.write(root2)<<endl;
		//getline(input,line);
	}
	return 0;
}

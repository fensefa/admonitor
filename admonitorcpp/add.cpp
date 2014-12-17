#include <iostream>
#include <fstream>
#include <cstdio>
#include <json/json.h>
#include <string>
#include "jsoncompute.h"
using namespace std;

/* this program is to merge data
 *
 * using like this 
 * ./a.out modulename 1.txt 2.txt
 *
 * */
int main(int argc, char **argv)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root,root2;
	string line;
	for(int i=3;i<argc;i++)
	{
		ifstream input(argv[i]);
		while(getline(input,line))
		{
			reader.parse(line,root);
			root2 = jsonAdd(root2,root);
			//jsonAddBy(root,root2);
			/*Json::Value kpis1,kpis2;
			kpis1 = root2["kpis"];
			kpis2 = root["kpis"];
			for(Json::Value::iterator it1 = kpis1.begin();it1 != kpis1.end();it1++)
			{
				bool existkpi = false;
				for(Json::Value::iterator it2 = kpis2.begin();it2 !=kpis2.end();it2++)
				{
					if((*it1)["kpi_name"] == (*it2)["kpi_name"])
					{
						*it2 = jsonAdd(*it2,*it1);
						existkpi = true;
					}
				}
				if(!existkpi)
					kpis2.append(*it1);
			}
			getline(input,line);
			root2["kpis"] = kpis2;*/
		}
	}
	root2["modulename"] = argv[1];
	root2["timeinterval"] = argv[2];
	ofstream output("mymeta.conf");
	output << writer.write(root2);
}

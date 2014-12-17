#include <iostream>
#include <fstream>
#include <cstdio>
#include <json/json.h>
#include <string>
using namespace std;

Json::Value jsonAdd(Json::Value, Json::Value);
Json::Value jsonDiv(Json::Value, Json::Value);
Json::Value kpiAdd(Json::Value, Json::Value, string);
Json::Value kpiDiv(Json::Value, Json::Value, string);
string jsonToString(Json::Value);

int main(int argc, char **argv)
{
	Json::Reader reader;
	Json::Value root;
	//ifstream input1("/public/admonitor/bak/indexserver/indexserver_kpi_10.168.9.237_20140814.log");
	//ifstream input2("/public/admonitor/bak/indexserver/indexserver_kpi_10.168.9.239_20140814.log");
	ofstream output1("m.txt");
	ofstream output2("h.txt");
	ofstream output3("d.txt");
	string line;
	Json::Value rootminute[288];
	time_t t = time(NULL);
	t = t / 86400 * 86400;
	for(int i=0;i<288;i++)
	{
		rootminute[i]["time"] = (unsigned int)(t + 300 * i);
	}
	cout<<"ok0\n";
	for(int i=1;i<argc;i++)
	{
		ifstream input(argv[i]);
		cout << "open " << argv[i] << endl;
		while(getline(input,line))
		{
			reader.parse(line,root);
			string x = root["time"].asString();
			unsigned int y = 0;
			for(int i = 0;i< 10;i++)
			{
				y *= 10;
				y += x[i] - 48;
			}
			root["time"] = root["time"].asString();
			int z = y % 86400 / 300;
			cout << "z=" << z <<endl;
			rootminute[z] = jsonAdd(rootminute[z], root);
			//root1["time"] = stoi(x);
			//cout << root1["time"].asUInt() << endl;
			cout << "ok1\n";
			getline(input,line);
		}
	}
	Json::Value roothour[24];
	Json::Value rootday;
	cout <<"ok3\n";
	for(int i=0;i<288;i++)
	{cout<<"i="<<i<<endl;
		roothour[i/12] = jsonAdd(roothour[i/12], rootminute[i]);
		rootday = jsonAdd(rootday,rootminute[i]);
	}
	cout << "ok2\n";
	for(int i=0;i<288;i++)
		output1 << jsonToString(rootminute[i]) << endl;
	for(int i=0;i<24;i++)
		output2 << jsonToString(roothour[i]) << endl;
	output3 << jsonToString(rootday) << endl;
}

string jsonToString(Json::Value jsvl)
{
	Json::StyledWriter writer;
	string str = writer.write(jsvl);
	int i=0, j=0;
	for(int i=0;i<str.size();i++)
		if(str[i] != '\n' && str[i] != ' ')
			str[j++] = str[i];
	str.resize(j);
	return str;
}

Json::Value kpiAdd(Json::Value kpi1, Json::Value kpi2, string kpi_name)
{
	Json::Value kpi3 = jsonAdd(kpi1, kpi2);
	kpi3["kpi_name"] = kpi_name;
	return kpi3;
}

Json::Value kpiDiv(Json::Value kpi1, Json::Value kpi2, string kpi_name)
{
	Json::Value kpi3 = jsonDiv(kpi1, kpi2);
	kpi3["kpi_name"] = kpi_name;
	return kpi3;
}

Json::Value jsonAdd(Json::Value jsvl1, Json::Value jsvl2)
{
	if(jsvl1.isNull())
		return jsvl2;
	if(jsvl2.isNull())
		return jsvl1;
	Json::Value jsvl3 = jsvl1;
	if(jsvl3.isArray() && jsvl2.isArray())
	{
		for(Json::Value::iterator it = jsvl3.begin(), it2 = jsvl2.begin();it != jsvl3.end(); it++, it2++)
		{
			*it = jsonAdd(*it, *it2);
		}

	}
	if(jsvl3.isObject() && jsvl2.isObject())
	{
		Json::Value::Members members = jsvl2.getMemberNames();
		for(int i=0;i<members.size();i++)
		{
			string key = members[i];
			jsvl3[key] = jsonAdd(jsvl3[key], jsvl2[key]);
		}
	}
	if(jsvl3.isUInt() && jsvl2.isUInt())
	{
		unsigned int a = jsvl3.asUInt();
		unsigned int b = jsvl2.asUInt();
		jsvl3 = a + b;
	}
	return jsvl3;

}

Json::Value jsonDiv(Json::Value jsvl1, Json::Value jsvl2)
{
	if(jsvl1.isNull())
		return jsvl1;
	if(jsvl2.isNull())
		return jsvl2;
	Json::Value jsvl3 = jsvl1;
	if(jsvl3.isArray() || jsvl3.isObject())
	{
		for(Json::Value::iterator it = jsvl3.begin(), it2 = jsvl2.begin();it != jsvl3.end(); it++, it2++)
			*it = jsonDiv(*it, *it2);

	}
	if(jsvl3.isUInt())
	{
		unsigned int a = jsvl3.asUInt();
		unsigned int b = jsvl2.asUInt();
		double x = a;
		double y = b;
		if(b != 0)
			jsvl3 = x / y;
		else
			jsvl3 = -1;
	}
	return jsvl3;
}

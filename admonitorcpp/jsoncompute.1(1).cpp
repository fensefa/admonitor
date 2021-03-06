#include "jsoncompute.h"
#include <string>
#include <iostream>

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

Json::Value jsonCompute(string json_op, Json::Value jsvl1, Json::Value jsvl2)
{
	if(json_op == "/" || json_op == "div")
		return jsonDiv(jsvl1,jsvl2);
	if(json_op == "+" || json_op == "add")
		return jsonAdd(jsvl1,jsvl2);
	if(json_op == "-" || json_op == "sub")
		return jsonSub(jsvl1,jsvl2);
	Json::Value ret;
	return ret;
}

Json::Value jsonCompute(string json_op, Json::Value jsvl, int base)
{
	if(json_op == "/" || json_op == "div")
		return jsonDiv(jsvl ,base);
	if(json_op == "*" || json_op == "mul")
		return jsonMul(jsvl, base);
	Json::Value ret;
	return ret;
}

Json::Value kpiCompute(string kpi_name, string kpi_op, Json::Value kpi1, Json::Value kpi2)
{
	Json::Value kpi;
	if(kpi_op == "/")
		kpi = jsonDiv(kpi1,kpi2);
	/*if(kpi_op == "Mul")
		kpi = jsonMul(kpi1,kpi2);*/
	if(kpi_op == "+")
		kpi = jsonAdd(kpi1,kpi2);
	if(kpi_op == "-")
		kpi = jsonSub(kpi1,kpi2);
	kpi["kpi_name"] = kpi_name;
	kpi["kpi_op"] = kpi_op;
	return kpi;
}

Json::Value kpiCompute(string kpi_name, string kpi_op, Json::Value kpi1, int base)
{
	Json::Value kpi;
	if(kpi_op == "/")
		kpi = jsonDiv(kpi1,base);
	if(kpi_op == "*")
		kpi = jsonMul(kpi1,base);
	kpi["kpi_name"] = kpi_name;
	kpi["kpi_op"] = kpi_op;
	return kpi;
}

Json::Value jsonAdd(Json::Value jsvl1, Json::Value jsvl2)
{
	if(jsvl1.empty())
		return jsvl2;
	if(jsvl2.empty())
		return jsvl1;
	if(jsvl1.isArray() && jsvl2.isArray())
	{
		if(jsvl1.size() != jsvl2.size())
			return jsvl1;
		for(Json::Value::iterator it1 = jsvl1.begin(), it2 = jsvl2.begin();it1 != jsvl1.end(); it1++, it2++)
		{
			*it1 = jsonAdd(*it1, *it2);
		}

	}
	if(jsvl1.isObject() && jsvl2.isObject())
	{
		Json::Value::Members members = jsvl2.getMemberNames();
		for(int i=0;i<members.size();i++)
		{
			string key = members[i];
			jsvl1[key] = jsonAdd(jsvl1[key], jsvl2[key]);
		}
	}
	if(jsvl1.isUInt() && jsvl2.isUInt())
	{
		unsigned int a = jsvl1.asUInt();
		unsigned int b = jsvl2.asUInt();
		jsvl1 = a + b;
	}
	return jsvl1;

}

Json::Value jsonSub(Json::Value jsvl1, Json::Value jsvl2)
{
	if(jsvl1.isNull())
		return jsvl2;
	if(jsvl2.isNull())
		return jsvl1;
	if(jsvl1.isArray() && jsvl2.isArray())
	{
		if(jsvl1.size() != jsvl2.size())
			return jsvl1;
		for(Json::Value::iterator it1 = jsvl1.begin(), it2 = jsvl2.begin();it1 != jsvl1.end(); it1++, it2++)
		{
			*it1 = jsonSub(*it1, *it2);
		}

	}
	if(jsvl1.isObject() && jsvl2.isObject())
	{
		Json::Value::Members members = jsvl2.getMemberNames();
		for(int i=0;i<members.size();i++)
		{
			string key = members[i];
			jsvl1[key] = jsonSub(jsvl1[key], jsvl2[key]);
		}
	}
	if(jsvl1.isUInt() && jsvl2.isUInt())
	{
		unsigned int a = jsvl1.asUInt();
		unsigned int b = jsvl2.asUInt();
		jsvl1 = a - b;
	}
	return jsvl1;
}

Json::Value jsonDiv(Json::Value jsvl1, Json::Value jsvl2)
{
	if(jsvl1.isNull())
		return jsvl1;
	if(jsvl2.isNull())
		return jsvl2;
	if(jsvl1.isArray() || jsvl1.isObject())
	{
		if(jsvl1.size() != jsvl2.size())
			return jsvl1;
		for(Json::Value::iterator it1 = jsvl1.begin(), it2 = jsvl2.begin();it1 != jsvl1.end(); it1++, it2++)
			*it1 = jsonDiv(*it1, *it2);

	}
	if(jsvl1.isUInt() && jsvl1.isUInt())
	{
		unsigned int a = jsvl1.asUInt();
		unsigned int b = jsvl2.asUInt();
		double x = a;
		double y = b;
		if(b != 0)
			jsvl1 = x / y;
		else
			jsvl1 = -1;
	}
	return jsvl1;
}

Json::Value jsonDiv(Json::Value jsvl, int base)
{
	if(jsvl.isArray() || jsvl.isObject())
	{
		for(Json::Value::iterator it = jsvl.begin();it != jsvl.end(); it++)
			*it = jsonDiv(*it, base);

	}

	if(jsvl.isInt())
	{
		int a = jsvl.asInt();
		if(base != 0)
			jsvl = a / base;
		else
			jsvl = -1;
	}

	return jsvl;
}

Json::Value jsonMul(Json::Value jsvl, int base)
{
	if(jsvl.isArray() || jsvl.isObject())
	{
		for(Json::Value::iterator it = jsvl.begin();it != jsvl.end(); it++)
			*it = jsonMul(*it, base);
	}
	if(jsvl.isUInt())
	{
		unsigned int a = jsvl.asUInt();
		jsvl = a * base;
	}
	return jsvl;
}

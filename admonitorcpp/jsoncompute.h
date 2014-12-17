#include <json/json.h>
#include <string>
using namespace std;

string jsonToString(Json::Value);

Json::Value kpiCompute(string, string, Json::Value, Json::Value);

Json::Value kpiCompute(string, string, Json::Value, int);

Json::Value jsonCompute(string, Json::Value, Json::Value);

Json::Value jsonCompute(string, Json::Value, int);

Json::Value jsonAdd(Json::Value, Json::Value);

Json::Value jsonSub(Json::Value, Json::Value);

Json::Value jsonDiv(Json::Value, Json::Value);

Json::Value jsonDiv(Json::Value, int);

Json::Value jsonMul(Json::Value, int);

void jsonAddBy(const Json::Value&, Json::Value&);

void jsonSubBy(const Json::Value&, Json::Value&);

void jsonDivBy(const Json::Value&, Json::Value&);

void JsonDivBy(const int base, Json::Value&);

void JsonMulBy(const int base, Json::Value&);

void getOpposite(Json::Value&);

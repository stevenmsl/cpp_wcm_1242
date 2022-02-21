
#include "util.h"
#include <cstring>
#include <vector>
#include <string>
#include <sstream>

using namespace sol1242;

string Util::toString(vector<string> input)
{
    string result = "[";
    for (auto e : input)
    {
        result += e;
        result += ",";
    }
    /* remove the last comma */
    if (result.back() == ',')
        result.pop_back();
    result += "]";
    return result;
}

string Util::toString(vector<int> input)
{
    string result = "[";
    for (auto e : input)
    {
        result += to_string(e);
        result += ",";
    }
    /* remove the last comma */
    if (result.back() == ',')
        result.pop_back();
    result += "]";
    return result;
}
#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;
namespace sol1242
{
  class HtmlParser
  {
  private:
    unordered_map<string, vector<string>> _urls;
    // Return a list of all urls from a webpage of given url.
  public:
    HtmlParser(vector<string> urls, vector<vector<int>> edges);
    vector<string> getUrls(string url);
  };

  class Solution
  {
  private:
  public:
    static vector<string> crawl(string startUrl, HtmlParser htmlParser);
  };
}
#endif
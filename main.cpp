#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol1242;

/*
Input:
urls = [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.google.com",
  "http://news.yahoo.com/us"
]
edges = [[2,0],[2,1],[3,2],[3,1],[0,4]]
startUrl = "http://news.yahoo.com/news/topics/"
Output: [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.yahoo.com/us"
]
*/
tuple<string, vector<string>, vector<vector<int>>, vector<string>>
testFixture1()
{
  auto urls = vector<string>{
      "http://news.yahoo.com",
      "http://news.yahoo.com/news",
      "http://news.yahoo.com/news/topics/",
      "http://news.google.com",
      "http://news.yahoo.com/us"};
  auto edges = vector<vector<int>>{
      {2, 0}, {2, 1}, {3, 2}, {3, 1}, {0, 4}};
  auto output = vector<string>{
      "http://news.yahoo.com",
      "http://news.yahoo.com/news",
      "http://news.yahoo.com/news/topics/",
      "http://news.yahoo.com/us"};
  string startUrl = "http://news.yahoo.com/news/topics/";

  return make_tuple(startUrl, urls, edges, output);
}

/*
Input:
urls = [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.google.com"
]
edges = [[0,2],[2,1],[3,2],[3,1],[3,0]]
startUrl = "http://news.google.com"
Output: ["http://news.google.com"]
Explanation: The startUrl links to all other pages that do not share the same hostname.
*/
tuple<string, vector<string>, vector<vector<int>>, vector<string>>
testFixture2()
{
  auto urls = vector<string>{
      "http://news.yahoo.com",
      "http://news.yahoo.com/news",
      "http://news.yahoo.com/news/topics/",
      "http://news.google.com"};
  auto edges = vector<vector<int>>{
      {0, 2}, {2, 1}, {3, 2}, {3, 1}, {3, 0}};
  auto output = vector<string>{
      "http://news.google.com"};
  string startUrl = "http://news.google.com";

  return make_tuple(startUrl, urls, edges, output);
}

void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see " << Util::toString(get<3>(f)) << endl;
  auto parser = HtmlParser(get<1>(f), get<2>(f));
  auto result = Solution::crawl(get<0>(f), parser);
  cout << "result: " << Util::toString(result) << endl;
}

void test2()
{
  auto f = testFixture2();
  cout << "Test 2 - exepct to see " << Util::toString(get<3>(f)) << endl;
  auto parser = HtmlParser(get<1>(f), get<2>(f));
  auto result = Solution::crawl(get<0>(f), parser);
  cout << "result: " << Util::toString(result) << endl;
}

void testParser()
{
  auto f = testFixture1();
  cout << "Test Parser - exepct to see "
       << "[http://news.yahoo.com,http://news.yahoo.com/news]" << endl;
  auto parser = HtmlParser(get<1>(f), get<2>(f));
  auto result = parser.getUrls(get<0>(f));
  cout << "result: " << Util::toString(result) << endl;
}

main()
{
  test1();
  test2();
  // testParser();
  return 0;
}
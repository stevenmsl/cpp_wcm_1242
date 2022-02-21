#include "solution.h"
#include "util.h"
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace sol1242;
using namespace std;

/*takeaways
  - refer to question 1242 for background info
  - for multithreaded implementation
    - use an infinite loop, and the exit condition
      is when the queue empty
    - acquire lock before modifying shared
      resources
*/

HtmlParser::HtmlParser(vector<string> urls, vector<vector<int>> edges)
{
  for (auto e : edges)
    _urls[urls[e[0]]].push_back(urls[e[1]]);
}

vector<string> HtmlParser::getUrls(string url)
{
  return _urls[url];
}

vector<string> Solution::crawl(string startUrl, HtmlParser htmlParser)
{
  auto result = vector<string>();
  auto q = queue<string>();
  auto visited = unordered_set<string>();

  q.push(startUrl);

  auto host = [](auto &s)
  {
    auto input = stringstream(s);
    string token;
    getline(input, token, '/'); // skip http:
    getline(input, token, '/'); // skip ''
    getline(input, token, '/');
    return token;
  };

  /* number of concurrent threads supported */
  const int N = thread::hardware_concurrency();
  auto threads = vector<thread>();
  auto mtx = mutex();
  auto cv = condition_variable();

  auto work = [&]()
  {
    while (true)
    {
      auto lock = unique_lock(mtx);
      /*
        - wait for a bit unless there
          is something in the queue
        - stop waiting for q.size() > 0
      */
      cv.wait_for(lock, 30ms, [&q]()
                  { return q.size(); });
      /* no more work left */
      if (q.empty())
        return;
      auto url = q.front();
      q.pop();
      lock.unlock();

      /*
        - reading only and requires no lock
      */
      auto urls = htmlParser.getUrls(url);

      lock.lock();
      visited.insert(url);
      result.push_back(url);
      for (auto u : urls)
        if (visited.count(u) == 0 && host(url) == host(u))
          q.push(u);
      lock.unlock();
      cv.notify_all();
    }
  };

  /* kick off the workers */
  for (auto i = 0; i < N; i++)
    /*
       - provide the work function to the
         thread constructor using emplace_back
    */
    threads.emplace_back(work);

  /* wait until everyone finish */
  for (auto &t : threads)
    t.join();

  return result;
}

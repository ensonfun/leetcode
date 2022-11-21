/*
https://www.lintcode.com/problem/892/
https://leetcode.com/problems/alien-dictionary/

269. Alien Dictionary
There is a new alien language which uses the latin alphabet.
However, the order among letters are unknown to you.
You receive a list of non-empty words from the dictionary, where words are
sorted lexicographically by the rules of this new language. Derive the order of
letters in this language. Example 1: Given the following words in dictionary,
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf".
Example 2:
Given the following words in dictionary,
[
  "z",
  "x"
]
The correct order is: "zx".
Example 3:
Given the following words in dictionary,
[
  "z",
  "x",
  "z"
]
The order is invalid, so return "".
Note:
You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the
given dictionary. If the order is invalid, return an empty char. There may be
multiple valid order of letters, return any one of them is fine.
*/

/*
[
  "wrf",
  "wrk",
  "er",
  "ett",
  "ek"
]

拓扑排序：拓扑排序的思路是，构建一个图，记录下图中每个节点的入度
每次讲入度为0的节点加入到queue，然后 pop
每次 pop 完，更新其它关联节点的入度-1，如果有新的==0，则加入到queue
如此反复
结束条件：没有为0的入度节点在queue中
如果还有>0的入度，则说明有环

具体到这道题，依次比较两个相邻的字符串，找到第一个不同的字符，即可定义先后关系
wrf,wrk ==> f->k
wrk,er ==> w->e

*/

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
 public:
  string alienOrder(vector<string>& words) {
    if (words.empty()) {
      return "";
    }

    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> degrees;
    for (auto w : words) {
      for (auto c : w) {
        degrees[c] = 0;
      }
    }

    buildGraph(words, graph, degrees);
    queue<char> zero_degree_chars;
    for (auto d : degrees) {
      if (d.second == 0) {
        zero_degree_chars.push(d.first);
      }
    }

    string ans;
    while (!zero_degree_chars.empty()) {
      auto cur = zero_degree_chars.front();
      zero_degree_chars.pop();
      ans.push_back(cur);

      for (auto sub : graph[cur]) {
        if (--degrees[sub] == 0) {
          zero_degree_chars.push(sub);
        }
      }
    }

    for (auto d : degrees) {
      if (d.second > 0) {
        return "";
      }
    }
    return ans;
  }

  void buildGraph(const vector<string>& words,
                  unordered_map<char, unordered_set<char>>& graph,
                  unordered_map<char, int>& degrees) {
    for (int i = 0; i != words.size() - 1; ++i) {
      auto cur = words[i];
      auto next = words[i + 1];
      int min_len = min(cur.size(), next.size());
      for (int j = 0; j != min_len; ++j) {
        if (cur[j] != next[j]) {
          if (graph.find(cur[j]) == graph.end()) {
            graph[cur[j]] = unordered_set<char>();
          }

          if (graph[cur[j]].find(next[j]) == graph[cur[j]].end()) {
            graph[cur[j]].insert(next[j]);
            degrees[next[j]]++;
          }

          break;
        }
      }
    }
  }
};

int main() {
  vector<string> input = {"wrt", "wrf", "er", "ett", "rftt"};

  Solution s;
  auto ans = s.alienOrder(input);
  assert(ans == "wertf");

  // circle, invalid
  vector<string> input1 = {"ab", "cd", "ae"};
  assert(s.alienOrder(input1) == "");

  vector<string> input2 = {"a", "b", "c"};
  assert(s.alienOrder(input2) == "abc");
  return 0;
}

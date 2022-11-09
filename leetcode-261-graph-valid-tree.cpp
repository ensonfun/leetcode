// https://leetcode.com/problems/graph-valid-tree/
// https://www.lintcode.com/problem/178/
// Given n nodes labeled from 0 to n-1 and a list of undirected edges (each edge
// is a pair of nodes), write a function to check whether these edges make up a
// valid tree.

// Example 1:

// Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
// Output: true
// Example 2:

// Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
// Output: false

// no cycle
// no broken(two or more trees)

#include <set>
#include <vector>
using namespace std;

class Solution {
 public:
  bool validTree(int n, vector<vector<int>>& edges) {
    if (n == 0 || edges.empty() || edges[0].empty()) {
      return false;
    }

    vector<int> parents(n, -1);
    for (int i = 0; i != edges.size(); ++i) {
      int parent1 = getParent(edges[i][0], parents);
      int parent2 = getParent(edges[i][1], parents);

      if (parent1 == parent2) {
        return false;
      }

      connect(parent1, parent2, parents);
    }

    // each node should has same root parent
    // otherwise it not a tree
    int common_parent = getParent(0, parents);
    for (auto p : parents) {
      if (common_parent != getParent(p, parents)) {
        return false;
      }
    }

    return true;
  }

  void connect(int node1, int node2, vector<int>& parents) {
    parents[node1] = node2;
  }

  int getParent(int node, const vector<int>& parents) {
    while (parents[node] != -1) {
      node = parents[node];
    }

    return node;
  }
};

int main() {
  // Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
  // Output: true
  Solution s;
  vector<vector<int>> input = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
  bool ret = s.validTree(5, input);
  assert(true == ret);

  // Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
  // Output: false
  input = {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
  ret = s.validTree(5, input);
  assert(false == ret);

  return 0;
}
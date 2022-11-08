// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
// https://github.com/eMahtab/number-of-connected-components-in-an-undirected-graph

// <!-- Given n nodes labeled from 0 to n - 1 and a list of undirected edges
// (each edge is a pair of nodes), write a function to find the number of
// connected components in an undirected graph.

// Example 1:

// Input: n = 5 and edges = [[0, 1], [1, 2], [3, 4]]

//      0          3
//      |          |
//      1 --- 2    4

// Output: 2
// Example 2:

// Input: n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]]

//      0           4
//      |           |
//      1 --- 2 --- 3

// Output:  1
// Note:
// You can assume that no duplicate edges will appear in edges. Since all edges
// are undirected, [0, 1] is the same as [1, 0] and thus will not appear
// together in edges. -->

#include <set>
#include <vector>
using namespace std;

class Solution {
 public:
  int countComponents(int n, vector<vector<int>>& edges) {
    if (n == 0 || edges.empty()) {
      return 0;
    }

    if (n == 1 || edges.size() == 1) {
      return 1;
    }

    // index of array start from 1
    vector<int> parents(n + 1, -1);

    for (int i = 0; i != edges.size(); ++i) {
      int parent1 = getParent(edges[i][0], parents);
      int parent2 = getParent(edges[i][1], parents);
      if (parent1 != parent2) {
        connect(parent1, parent2, parents);
      }
    }

    set<int> uniq_parents;
    for (int i = 1; i != parents.size(); ++i) {
      uniq_parents.insert(getParent(parents[i], parents));
    }

    return uniq_parents.size();
  }

  void connect(int node1, int node2, vector<int>& parents) {
    parents[node1] = node2;
  }

  int getParent(int node, vector<int>& parents) {
    while (parents[node] != -1) {
      node = parents[node];
    }

    return node;
  }
};

int main() {
  // Input: n = 5 and edges = [[0, 1], [1, 2], [3, 4]]
  Solution s;
  vector<vector<int>> input = {{0, 1}, {1, 2}, {3, 4}};
  int ret = s.countComponents(5, input);
  assert(2 == ret);

  // Input: n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]]
  input = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
  ret = s.countComponents(5, input);
  assert(1 == ret);
  return 0;
}

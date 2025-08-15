#include <bits/stdc++.h>
using namespace std;

/*
 Problem:
 --------
 We are given a DAG (Directed Acyclic Graph) with n nodes.
 Each node i has a score[i].
 We must process the nodes in a valid topological order.
 Each node gets a position (1-based) in the processing order.
 Profit = sum(score[node] * position_in_order) over all nodes.
 Goal: Find the maximum possible profit achievable by choosing the optimal topological order.

 Approach:
 ---------
 This is a "maximum weighted topological ordering" problem.

 1. Because the graph is a DAG, there exists at least one valid topological ordering.
 2. We can solve this using Bitmask Dynamic Programming:
    - `mask` represents the set of already processed nodes.
    - `premask[i]` is a bitmask of all prerequisites of node i.
    - We can process node i if:
          (premask[i] & mask) == premask[i]   (all prerequisites done)
          AND i is not already in `mask`.
    - Position in ordering = popcount(mask) + 1.
    - Recurrence:
         dp[mask] = max over available nodes i:
                     score[i] * position + dp[mask | (1 << i)]

 Complexity:
 -----------
 - n <= 22
 - States = 2^n
 - Transitions = O(n) per state
 - Time Complexity = O(n * 2^n)
 - Space Complexity = O(2^n)

---------------------------------------------------
 Diagram: How premask is built
---------------------------------------------------
 Example DAG:
     0 → 1 → 2
     ↑    ↘
     └──── 3

 Node numbering: 0, 1, 2, 3
 Edges: (0,1), (1,2), (0,3), (1,3)

 Step 1: premask array starts as [0, 0, 0, 0]  (n=4)

 Step 2: Process edges:
    Edge (0,1): premask[1] |= (1 << 0)   → premask[1] = 0001 (binary)
    Edge (1,2): premask[2] |= (1 << 1)   → premask[2] = 0010
    Edge (0,3): premask[3] |= (1 << 0)   → premask[3] = 0001
    Edge (1,3): premask[3] |= (1 << 1)   → premask[3] = 0011

 Final premask (binary):
   Node 0: 0000 → No prerequisites
   Node 1: 0001 → Needs node 0 before it
   Node 2: 0010 → Needs node 1 before it
   Node 3: 0011 → Needs nodes 0 and 1 before it

 Meaning: For example, Node 3 can only be taken if mask has both bit0 and bit1 set.
---------------------------------------------------
*/

class Solution {
public:
    int dp[1 << 22]; // dp[mask] = maximum profit starting from this set of processed nodes

    // Recursive DP function
    int maxProfit(vector<int>& premask, vector<int>& score, int mask) {
        int n = score.size();

        // Base case: all nodes are processed
        if (mask == ((1 << n) - 1)) return 0;

        // Memoization check
        if (dp[mask] != -1) return dp[mask];

        int ans = 0;
        int pos = __builtin_popcount(mask) + 1; // Current position in the ordering

        // Try every available node
        for (int i = 0; i < n; i++) {
            bool notTaken = !(mask & (1 << i));
            bool prereqDone = (premask[i] & mask) == premask[i];
            if (notTaken && prereqDone) {
                int profit = score[i] * pos + maxProfit(premask, score, mask | (1 << i));
                ans = max(ans, profit);
            }
        }

        return dp[mask] = ans;
    }

    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> premask(n, 0);

        // Build prerequisite bitmask for each node
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            premask[v] |= (1 << u);
        }

        memset(dp, -1, sizeof(dp));
        return maxProfit(premask, score, 0);
    }
};

/*
 Example usage:
 int main() {
     int n = 4;
     vector<vector<int>> edges = {{0,1},{1,2},{0,3},{1,3}};
     vector<int> score = {5, 10, 20, 15};
     Solution sol;
     cout << sol.maxProfit(n, edges, score) << "\n";
 }
*/

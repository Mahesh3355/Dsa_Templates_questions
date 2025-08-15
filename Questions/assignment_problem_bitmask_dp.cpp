#include <bits/stdc++.h>
using namespace std;

/*
 Problem:
 --------
 We have N workers and N jobs.
 Any worker can do any job, but each (worker, job) pair has a given cost.
 We must assign each worker exactly one job, and each job to exactly one worker,
 such that the total assignment cost is minimized.

 Input:
 ------
 N (number of workers and jobs)
 N x N cost matrix `C`, where C[i][j] = cost of assigning worker i to job j.

 Output:
 -------
 Minimum total cost of assigning jobs to workers.

 Approach:
 ---------
 This is a **classic Assignment Problem**.
 We solve it using **Bitmask Dynamic Programming**:

 State definition:
   dp[mask][i] = Minimum cost to assign jobs to workers starting from worker i,
                 when `mask` represents the set of jobs already assigned.

 Transition:
   For worker i, try assigning them to every job j not yet taken in `mask`:
      dp[mask][i] = min( cost[i][j] + dp[mask | (1 << j)][i + 1] )

 Base case:
   If i == n (all workers assigned), cost is 0.

 Complexity:
 -----------
 - Number of states: 2^N * N
 - Transition: O(N) per state
 - Time Complexity: O(N^2 * 2^N)
 - Space Complexity: O(N * 2^N)
 Works fine for N <= 20.
*/

// dp[mask][i] = Minimum cost for assigning jobs starting from worker i
int dp[1 << 20][20];

// Recursive DP function
int assign_dp(vector<vector<int>>& cost, int mask, int i) {
    int n = cost.size();

    // All workers are assigned
    if (i >= n) {
        return 0;
    }

    // Return already computed result
    if (dp[mask][i] != -1) {
        return dp[mask][i];
    }

    int ans = INT_MAX;

    // Try assigning worker i to each unassigned job j
    for (int j = 0; j < cost[i].size(); j++) {
        if (mask & (1 << j)) continue; // Skip if job j already taken

        // Take job j, add cost, and move to next worker
        int tk = assign_dp(cost, mask | (1 << j), i + 1) + cost[i][j];
        ans = min(ans, tk);
    }

    return dp[mask][i] = ans;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    // Read cost matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    // Initialize DP table with -1 (uncomputed)
    memset(dp, -1, sizeof(dp));

    cout << "Minimum cost is: " << assign_dp(cost, 0, 0) << endl;

    return 0;
}

/*
 Example:
 --------
 Input:
 3
 9 2 7
 6 4 3
 5 8 1

 Output:
 Minimum cost is: 9

 Explanation:
 Worker 0 → Job 1 (cost 2)
 Worker 1 → Job 2 (cost 3)
 Worker 2 → Job 0 (cost 5)
 Total = 2 + 3 + 5 = 10
*/

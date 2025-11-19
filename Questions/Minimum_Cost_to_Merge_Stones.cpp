/*
===========================================================
       Minimum Cost to Merge Stones (k group merging)
===========================================================

Problem:
--------
You may merge exactly k consecutive piles at a time.
Cost of merging = sum of stones in those k piles.

Goal:
-----
Merge all piles into ONE pile with minimum possible cost.
If impossible → return -1.

Key Observations:
-----------------
1. A merge reduces pile count by (k−1).
   Thus merging to ONE pile requires:
       (n - 1) % (k - 1) == 0

2. Use interval DP:
       dp[i][j] = minimum cost to merge interval [i..j]
                  into ANY number of piles.

3. A segment can form ONE pile only when:
       (j - i) % (k - 1) == 0

4. Valid splitting occurs in steps of (k−1):
       for (st = i; st < j; st += (k - 1))

===========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[35][35];
    vector<int> prefix;

    // Fast range sum using prefix sums
    int sum(int i, int j) {
        return prefix[j + 1] - prefix[i];
    }

    // Recursively compute dp using interval splitting
    int merge_Stone(vector<int> &stones, int i, int j, int k) {
        if (i >= j) return 0;    // already one pile
        if (dp[i][j] != -1) return dp[i][j];

        int ans = INT_MAX;

        // Try splitting only at valid points (step = k-1)
        for (int st = i; st < j; st += (k - 1)) {
            int left = merge_Stone(stones, i, st, k);
            int right = merge_Stone(stones, st + 1, j, k);
            ans = min(ans, left + right);
        }

        // If this segment size allows merging into ONE pile
        if ((j - i) % (k - 1) == 0) {
            ans += sum(i, j);
        }

        return dp[i][j] = ans;
    }

    int mergeStones(vector<int> &stones, int k) {
        int n = stones.size();

        // If merging to 1 pile is impossible
        if ((n - 1) % (k - 1) != 0) return -1;

        // Build prefix sums
        prefix.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }

        memset(dp, -1, sizeof(dp));

        return merge_Stone(stones, 0, n - 1, k);
    }
};

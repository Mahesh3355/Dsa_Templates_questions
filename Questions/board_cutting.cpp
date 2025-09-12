/*
    Problem: Board Cutting (Minimum Cost to cut board into squares)
    Category: Greedy
    Approach:
    - Sort both horizontal (y) and vertical (x) cut costs in descending order.
    - Always cut the larger cost first (greedy choice).
    - Maintain current horizontal (hc) and vertical (vc) segment counts.
    - Multiply cost by opposite segment count when adding to total.

    Complexity:
    - Sorting: O(n log n + m log m)
    - Iteration: O(n + m)
    - Total: O(n log n + m log m)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minCost(int n, int m, vector<int>& x, vector<int>& y) {
        sort(x.begin(), x.end(), greater<int>());
        sort(y.begin(), y.end(), greater<int>());

        long long hc = 1, vc = 1, ans = 0;
        int i = 0, j = 0;

        while (i < (int)x.size() && j < (int)y.size()) {
            if (x[i] >= y[j]) {
                ans += 1LL * x[i] * hc; 
                vc++;
                i++;
            } else {
                ans += 1LL * y[j] * vc;
                hc++;
                j++;
            }
        }
        while (i < (int)x.size()) {
            ans += 1LL * x[i] * hc;
            vc++; i++;
        }
        while (j < (int)y.size()) {
            ans += 1LL * y[j] * vc;
            hc++; j++;
        }
        return ans;
    }
};

// Example driver
int main() {
    int n = 4, m = 6;
    vector<int> x = {2, 1, 3, 1, 4}; // vertical cuts
    vector<int> y = {4, 1, 2};       // horizontal cuts

    Solution sol;
    cout << sol.minCost(n, m, x, y) << "\n"; // Expected 42
    return 0;
}

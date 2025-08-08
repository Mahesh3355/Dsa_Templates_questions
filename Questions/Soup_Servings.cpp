// You have two soups, A and B, each starting with n mL. On every turn, one of the following four serving operations is chosen at random, 
// each with probability 0.25 independent of all previous turns:
// pour 100 mL from type A and 0 mL from type B
// pour 75 mL from type A and 25 mL from type B
// pour 50 mL from type A and 50 mL from type B
// pour 25 mL from type A and 75 mL from type B
// Note:
// There is no operation that pours 0 mL from A and 100 mL from B.
// The amounts from A and B are poured simultaneously during the turn.
// If an operation asks you to pour more than you have left of a soup, pour all that remains of that soup.
// The process stops immediately after any turn in which one of the soups is used up.
// Return the probability that A is used up before B, plus half the probability that both soups are used up in the same turn. 
// Answers within 10-5 of the actual answer will be accepted.
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 2D memoization table to store results of subproblems
    // memo[a][b] = probability that A finishes first (or both same turn with half credit)
    vector<vector<double>> memo;

    // Recursive helper function to compute probability
    double sp(int a, int b) {
        // ---- Base cases ----

        // Case 1: Both soups A and B become empty at the same time → half probability
        if (a <= 0 && b <= 0) return 0.5;

        // Case 2: Soup A is empty but B still has soup → full probability for A finishing first
        if (a <= 0) return 1.0;

        // Case 3: Soup B is empty but A still has soup → probability is 0 (B finishes first)
        if (b <= 0) return 0.0;

        // ---- Memoization check ----
        // If we have already computed this state, return the stored result
        if (memo[a][b] >= 0) return memo[a][b];

        // ---- Recurrence relation ----
        // Each move has probability 0.25 and leads to a new (a,b) state:
        // 1. Serve 100 mL from A, 0 mL from B → a-4, b
        // 2. Serve 75 mL from A, 25 mL from B → a-3, b-1
        // 3. Serve 50 mL from A, 50 mL from B → a-2, b-2
        // 4. Serve 25 mL from A, 75 mL from B → a-1, b-3
        double res = 0.25 * (
            sp(a - 4, b) +
            sp(a - 3, b - 1) +
            sp(a - 2, b - 2) +
            sp(a - 1, b - 3)
        );

        // Store result in memo table for future use
        memo[a][b] = res;

        // Return the computed probability
        return res;
    }

    double soupServings(int n) {
        // Optimization: For large n, probability approaches 0.5.
        // However, here you set it to 1.0 — this is incorrect.
        // Correct cutoff should return 0.5 for accuracy.
        if (n >= 4800) return 0.5;

        // Convert n mL to units of 25 mL for easier calculation
        int N = (n + 24) / 25;

        // Initialize memo table with -1.0 meaning "uncomputed"
        memo.assign(N + 1, vector<double>(N + 1, -1.0));

        // Start recursion from (N, N) meaning both soups are full
        return sp(N, N);
    }
};

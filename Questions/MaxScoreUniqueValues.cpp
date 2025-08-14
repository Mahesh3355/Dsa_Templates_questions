/*
    Problem:
    --------
    You are given a 2D matrix `grid` of positive integers.
    You must select one or more cells such that:
        1. No two selected cells are from the same row.
        2. The values in the selected cells are unique.
    Your score is the sum of the values of selected cells.
    Return the maximum score possible.

    Approach:
    ---------
    - Transform the grid into a list of {value, rowIndex} pairs.
    - Sort the list in descending order of values (greedy preference for higher values).
    - Use recursion + memoization (DP with bitmasking) to explore:
        * Taking a value (if that row hasn't been used yet)
        * Skipping a value
    - The bitmask keeps track of which rows are already used.
    - While taking a value, skip all entries with the same value to ensure uniqueness.

    Complexity:
    -----------
    Let N = total cells in the matrix = rows * cols
    - Time: O(N log N) for sorting + O(N * 2^rows) for DP
    - Space: O(N * 2^rows) for memoization
*/

class Solution {
public:
    // Memoization map: key = (index, mask), value = max score
    map<pair<int, int>, int> dp;

    /*
        Recursive function to compute maximum score.
        values: list of {value, rowIndex} pairs (sorted in descending order by value)
        i: current index in values list
        mask: bitmask representing which rows are already used
    */
    int maxScore(vector<vector<int>>& values, int i, int mask) {
        // Base case: No more elements to consider
        if (i >= values.size()) {
            return 0;
        }

        // Return memoized result if already computed
        if (dp.find({i, mask}) != dp.end()) {
            return dp[{i, mask}];
        }

        // Option 1: Skip the current value
        int skipCurrent = maxScore(values, i + 1, mask);

        // Option 2: Take the current value (only if its row is unused)
        int takeCurrent = 0;
        if (!((1 << values[i][1]) & mask)) {
            // Move to the next index with a different value to ensure uniqueness
            int j = i;
            while (j < values.size() && values[i][0] == values[j][0]) {
                j++;
            }
            takeCurrent = values[i][0] + maxScore(values, j, mask | (1 << values[i][1]));
        }

        // Store and return the best of both options
        return dp[{i, mask}] = max(skipCurrent, takeCurrent);
    }

    int maxScore(vector<vector<int>>& grid) {
        vector<vector<int>> values;

        // Convert grid into a list of {value, rowIndex} pairs
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                values.push_back({grid[i][j], i});
            }
        }

        // Sort in descending order by value
        sort(values.begin(), values.end(), greater<vector<int>>());

        // Start recursive DP with initial index 0 and mask 0
        return maxScore(values, 0, 0);
    }
};

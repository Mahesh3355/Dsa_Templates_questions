#include <bits/stdc++.h>
using namespace std;

/*
📌 Problem:
You are given a 2D binary grid. 
Find 3 non-overlapping rectangles (with horizontal/vertical edges) that cover all `1`s in the grid, 
such that the sum of their areas is minimized.

Rectangles can touch, but must not overlap.

---

🔑 Key Observations:
1. Each rectangle is just the bounding box of some subset of 1s.
2. We must partition the grid into 3 valid rectangles.
3. Possible partitions:
   - 3 horizontal strips
   - 1 horizontal + 2 vertical strips (L-shape)
   - Symmetric cases (handled by rotating the grid)

---

🛠️ Approach:
- Define helper function `mini_area` to compute area of bounding box of 1’s in subgrid.
- Try all possible partitions:
    1. Split into 3 horizontal rectangles.
    2. Split into 1 horizontal (top) + 2 vertical (bottom).
    3. Rotate grid to simulate vertical cases.
- Take the minimum over all valid partitions.

---

ASCII Partition Sketches:
-----------------------------------------
Case 1: 3 Horizontal splits
+-------+
|   R1  |
+-------+
|   R2  |
+-------+
|   R3  |
+-------+

Case 2: 1 Horizontal + 2 Vertical
+-------+
|   R1  |
+---+---+
| R2| R3|
+---+---+

(Symmetric cases are handled by rotating the grid)

Time Complexity:
- O(n^2 * m^2) in worst case (but practical since we only split rows/cols).
*/

class Solution {
public:
    // Rotate the grid 90 degrees clockwise
    vector<vector<int>> rotate(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[m - j - 1][i] = grid[i][j];
            }
        }
        return ans;
    }

    // Compute area of bounding box of 1’s in subgrid [t..b][l..r]
    int mini_area(vector<vector<int>>& grid, int t, int b, int l, int r) {
        int min_i = 1e9, min_j = 1e9, max_i = -1, max_j = -1;
        for (int i = t; i <= b; i++) {
            for (int j = l; j <= r; j++) {
                if (grid[i][j]) {
                    min_i = min(min_i, i);
                    min_j = min(min_j, j);
                    max_i = max(max_i, i);
                    max_j = max(max_j, j);
                }
            }
        }
        // If no 1’s → invalid rectangle
        if (max_i < min_i) return INT_MAX / 3;
        return (max_i - min_i + 1) * (max_j - min_j + 1);
    }

    // Try all partitions (horizontal and L-shapes)
    int solve(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int res = INT_MAX;

        // Case 1: 1 horizontal split + 2 vertical (L-shape)
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < m - 1; j++) {
                res = min(res, 
                    mini_area(grid, 0, i, 0, m - 1) +
                    mini_area(grid, i + 1, n - 1, 0, j) +
                    mini_area(grid, i + 1, n - 1, j + 1, m - 1));

                res = min(res,
                    mini_area(grid, 0, i, 0, j) +
                    mini_area(grid, 0, i, j + 1, m - 1) +
                    mini_area(grid, i + 1, n - 1, 0, m - 1));
            }
        }

        // Case 2: 3 horizontal splits
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                res = min(res,
                    mini_area(grid, 0, i, 0, m - 1) +
                    mini_area(grid, i + 1, j, 0, m - 1) +
                    mini_area(grid, j + 1, n - 1, 0, m - 1));
            }
        }

        return res;
    }

    // Entry function
    int minimumSum(vector<vector<int>>& grid) {
        auto rgrid = rotate(grid);
        return min(solve(grid), solve(rgrid));
    }
};

#include <bits/stdc++.h>
using namespace std;

/*
Problem: Trapping Rain Water II (2D version)

Given an m x n integer matrix heightMap representing the height of each unit cell 
in a 2D elevation map, return the volume of water it can trap after raining.

Example 1:
Input: heightMap = [[1,4,3,1,3,2],
                    [3,2,1,3,2,4],
                    [2,3,3,2,3,1]]
Output: 4
Explanation: After the rain, water is trapped between the blocks.
             We have two small ponds 1 and 3 units trapped.
             Total trapped water = 4.

Example 2:
Input: heightMap = [[3,3,3,3,3],
                    [3,2,2,2,3],
                    [3,2,1,2,3],
                    [3,2,2,2,3],
                    [3,3,3,3,3]]
Output: 10

Constraints:
1 <= m, n <= 200
0 <= heightMap[i][j] <= 2 * 10^4
*/

// --------------------- Solution ---------------------
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        vector<int> dRow = {0, 0, -1, 1}; // directions: left, right, up, down
        vector<int> dCol = {-1, 1, 0, 0};

        int numOfRows = heightMap.size();
        if(numOfRows == 0) return 0;
        int numOfCols = heightMap[0].size();
        if(numOfCols == 0) return 0;

        vector<vector<bool>> visited(numOfRows, vector<bool>(numOfCols, false));
        priority_queue<Cell> boundary;

        // Push all boundary cells into the min-heap
        for (int i = 0; i < numOfRows; i++) {
            boundary.push(Cell(heightMap[i][0], i, 0));
            boundary.push(Cell(heightMap[i][numOfCols - 1], i, numOfCols - 1));
            visited[i][0] = visited[i][numOfCols - 1] = true;
        }
        for (int j = 0; j < numOfCols; j++) {
            boundary.push(Cell(heightMap[0][j], 0, j));
            boundary.push(Cell(heightMap[numOfRows - 1][j], numOfRows - 1, j));
            visited[0][j] = visited[numOfRows - 1][j] = true;
        }

        int totalWaterVolume = 0;

        // Process cells from the lowest boundary upwards
        while (!boundary.empty()) {
            Cell currentCell = boundary.top();
            boundary.pop();

            int currentRow = currentCell.row;
            int currentCol = currentCell.col;
            int minBoundaryHeight = currentCell.height;

            // Explore all 4 neighbors
            for (int direction = 0; direction < 4; direction++) {
                int neighborRow = currentRow + dRow[direction];
                int neighborCol = currentCol + dCol[direction];

                if (isValidCell(neighborRow, neighborCol, numOfRows, numOfCols) &&
                    !visited[neighborRow][neighborCol]) {

                    int neighborHeight = heightMap[neighborRow][neighborCol];

                    // Water trapped if neighbor is lower than current boundary
                    if (neighborHeight < minBoundaryHeight) {
                        totalWaterVolume += minBoundaryHeight - neighborHeight;
                    }

                    // Push neighbor into heap with updated height
                    boundary.push(Cell(max(neighborHeight, minBoundaryHeight), neighborRow, neighborCol));
                    visited[neighborRow][neighborCol] = true;
                }
            }
        }

        return totalWaterVolume;
    }

private:
    // Class to represent a cell in the height map
    class Cell {
    public:
        int height, row, col;
        Cell(int h, int r, int c) : height(h), row(r), col(c) {}
        bool operator<(const Cell& other) const { return height >= other.height; } // min-heap
    };

    // Check if a cell is within bounds
    bool isValidCell(int row, int col, int numOfRows, int numOfCols) {
        return row >= 0 && col >= 0 && row < numOfRows && col < numOfCols;
    }
};

// --------------------- Main Function (User Input) ---------------------
int main() {
    int m, n;
    cout << "Enter number of rows (m): "<<endl;
    cin >> m;
    cout << "Enter number of columns (n): "<<endl;
    cin >> n;

    vector<vector<int>> heightMap(m, vector<int>(n));

    cout << "Enter the height map matrix (" << m << " x " << n << "):\n";
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> heightMap[i][j];
        }
    }

    Solution sol;
    int trappedWater = sol.trapRainWater(heightMap);
    cout << "Total Trapped Water: " << trappedWater << endl;

    return 0;
}

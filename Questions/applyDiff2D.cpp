// You are given a 2D integer matrix mat[][] of size n × m and a list of q operations opr[][]. Each operation is represented as an array [v, r1, c1, r2, c2],where:
// v is the value to be added
// (r1, c1) is the top-left cell of a submatrix
// (r2, c2) is the bottom-right cell of the submatrix (inclusive)
// For each of the q operations, add v to every element in the submatrix from (r1, c1) to (r2, c2). Return the final matrix after applying all operations.
class Solution {
  public:
    vector<vector<int>> applyDiff2D(vector<vector<int>>& mat,
                                    vector<vector<int>>& opr) {
        int n = mat.size();
        int m = mat[0].size();
        
        // Step 1: Create a difference matrix with padding to avoid out-of-bound errors
        vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0));
        
        // Step 2: Apply each operation using the 2D difference matrix trick
        for (auto& op : opr) {
            int v = op[0];
            int r1 = op[1], c1 = op[2];
            int r2 = op[3], c2 = op[4];
            
            // We add 'v' at the top-left of the submatrix
            diff[r1][c1] += v;
            
            // Subtract 'v' to the right of the submatrix
            diff[r1][c2 + 1] -= v;
            
            // Subtract 'v' just below the submatrix
            diff[r2 + 1][c1] -= v;
            
            // Add back 'v' to fix double subtraction at bottom-right+1
            diff[r2 + 1][c2 + 1] += v;
        }
        
        // Step 3: Row-wise prefix sum to accumulate horizontal changes
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                diff[i][j] += diff[i][j - 1];
            }
        }

        // Step 4: Column-wise prefix sum to accumulate vertical changes
        for (int j = 0; j < m; ++j) {
            for (int i = 1; i < n; ++i) {
                diff[i][j] += diff[i - 1][j];
            }
        }

        // Step 5: Add the resulting difference matrix to the original matrix
        vector<vector<int>> result = mat;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result[i][j] += diff[i][j];
            }
        }
        
        return result;
    }
};

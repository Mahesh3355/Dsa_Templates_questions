/*
    Problem: Partition an array of 2n integers into two arrays of size n 
             such that the absolute difference of their sums is minimized.

    Approach: Meet in the Middle (Optimized Subset Sum)
    - Split the array into two halves of size n.
    - Generate all possible subset sums of each half and group them by subset size (using bitmask).
    - For every possible split (i elements from first half and n - i from second half),
      try to find subset sums that together make the total sum closest to sum/2.
    - Use binary search (lower_bound) for efficient search on sorted sums.
    - Return the minimum absolute difference between two partitions.
*/

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        // Step 1: Sort the array (optional, not required here but may help in debugging or optimizing)
        sort(nums.begin(), nums.end());

        int sum = accumulate(nums.begin(), nums.end(), 0); // total sum of all elements
        int n = nums.size() / 2; // size of one partition
        map<int, vector<int>> p1, p2; // maps to store subset sums by size

        // Step 2: Generate all subsets of the first and second half using bitmask
        for (int i = 0; i < (1 << n); i++) {
            int sum1 = 0, sum2 = 0;
            for (int j = 0; j < n; j++) {
                if ((1 << j) & i) {
                    sum1 += nums[j];
                    sum2 += nums[n + j];
                }
            }
            int cnt = __builtin_popcount(i); // number of elements in subset
            p1[cnt].push_back(sum1);
            p2[cnt].push_back(sum2);
        }

        // Step 3: Sort all subsets for binary search
        for (auto& i : p1) sort(i.second.begin(), i.second.end());
        for (auto& i : p2) sort(i.second.begin(), i.second.end());

        int ans = INT_MAX;

        // Step 4: Try all combinations of i elements from first half and n-i from second
        for (auto& [ele, vs] : p1) {
            int need = n - ele;
            if (p2.count(need)) {
                for (int j : vs) {
                    int rem = sum / 2 - j; // we want total (j + other) to be close to sum/2
                    auto& vec = p2[need];
                    auto it = lower_bound(vec.begin(), vec.end(), rem);
                    if (it != vec.end()) {
                        int k = *it;
                        ans = min(ans, abs(sum - 2 * (j + k))); // total1 = j + k, total2 = sum - (j + k)
                    }
                }
            }
        }

        return ans;
    }
};

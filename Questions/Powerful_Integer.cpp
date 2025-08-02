// You are given a 2D integer array intervals[][] of length n, where each intervals[i] = [start, end] represents a closed interval 
// (i.e., all integers from start to end, inclusive). You are also given an integer k. An integer is called Powerful if it appears in at least k intervals. 
// Find the maximum Powerful Integer.
// Note: If no integer occurs at least k times return -1
class Solution {
public:
    // Static comparator to sort intervals by end time (and by start if ends are equal)
    static bool cmp(vector<int>& a, vector<int>& b) {
        if (a[1] != b[1]) 
            return a[1] < b[1];  // sort by increasing end time
        return a[0] < b[0];      // if ends are equal, sort by increasing start time
    }

    int powerfulInteger(vector<vector<int>>& intervals, int k) {
        // Step 1: Sort the intervals by end time
        sort(intervals.begin(), intervals.end(), cmp);

        // Step 2: Extract and sort all start points separately
        vector<int> starts;
        for (auto& interval : intervals) {
            starts.push_back(interval[0]);
        }
        sort(starts.begin(), starts.end());

        int ans = -1;
        int n = intervals.size();

        // Step 3: For each interval (sorted by end), check how many intervals start before or at that end
        for (int i = 0; i < n; i++) {
            int endTime = intervals[i][1];

            // Find the number of intervals whose start <= endTime using upper_bound
            int index = upper_bound(starts.begin(), starts.end(), endTime) - starts.begin();

            int count = index - i;  // number of overlapping intervals with current endTime

            // Step 4: If count >= k, update the answer
            if (count >= k) {
                ans = max(ans, endTime);
            }
        }

        return ans;  // final answer, or -1 if no such point exists
    }
};

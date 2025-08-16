#include <bits/stdc++.h>
using namespace std;

/*
Problem:
---------
Given a string s (digits '0'..'4') and integer k,
find the maximum difference between freq[a] - freq[b] over all substrings
of length ≥ k, such that:
  - Character 'a' appears an odd number of times
  - Character 'b' appears a non-zero even number of times

Approach:
---------
1. Enumerate every pair (a, b), where a != b.
2. Use a two-pointer sliding window with prefix counts.
   - cnt_a, cnt_b = counts up to "right"
   - prev_a, prev_b = counts up to "left"
3. Encode parity state of (a, b) as 2 bits:
      status = (cnt_a % 2) << 1 | (cnt_b % 2)
   So possible states = [00, 01, 10, 11].
4. Maintain best[state] = minimum value of (prev_a - prev_b) seen
   for substrings starting at valid "left".
   - "left" is valid if substring length ≥ k
     and substring contains at least 2 b’s.
5. At each "right", check:
   - Required left state = status_right ^ 0b10
   - Update answer as: (cnt_a - cnt_b) - best[required_state]

Time Complexity:
---------------
- O(20 * n), since we try at most 20 pairs of (a, b),
  and each pass over the string is O(n).
- Works efficiently for n ≤ 3e4.

*/

class Solution {
public:
    int maxDifference(string s, int k) {
        auto getStatus = [](int cnt_a, int cnt_b) -> int {
            return ((cnt_a & 1) << 1) | (cnt_b & 1);
        };

        int n = s.size();
        int ans = INT_MIN;

        for (char a = '0'; a <= '4'; ++a) {
            for (char b = '0'; b <= '4'; ++b) {
                if (a == b) continue;

                // best[state] = minimum value of (prev_a - prev_b)
                // for any valid left with that parity state
                int best[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
                int cnt_a = 0, cnt_b = 0;
                int prev_a = 0, prev_b = 0;
                int left = -1;

                for (int right = 0; right < n; ++right) {
                    cnt_a += (s[right] == a);
                    cnt_b += (s[right] == b);

                    // Try to advance left so substring [left+1 .. right] is valid
                    while (right - left >= k && cnt_b - prev_b >= 2) {
                        int left_status = getStatus(prev_a, prev_b);
                        best[left_status] =
                            min(best[left_status], prev_a - prev_b);
                        ++left;
                        prev_a += (s[left] == a);
                        prev_b += (s[left] == b);
                    }

                    int right_status = getStatus(cnt_a, cnt_b);
                    int required = right_status ^ 0b10;
                    if (best[required] != INT_MAX) {
                        ans = max(ans,
                                  cnt_a - cnt_b - best[required]);
                    }
                }
            }
        }
        return ans;
    }
};

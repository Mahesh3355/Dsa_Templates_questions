// Given a string s, find the length of longest periodic proper prefix of s. If no such prefix exists, return -1.
// A periodic proper prefix is a non empty prefix of s (but not the whole string), such that repeating this prefix enough times produces a string that starts with s.
class Solution {
public:
    // Compute the Z-function for string s
    // z[i] = length of the longest substring starting at i
    //        that is also a prefix of s
    // Time complexity: O(n)
    vector<int> zFunction(string &s) {
        int n = s.length();
        vector<int> z(n, 0);
        int l = 0, r = 0; // current [l, r] window of matched prefix

        for (int i = 1; i < n; i++) {
            // If i is inside the current [l, r] match window,
            // initialize z[i] to the min possible without exceeding r
            if (i <= r) {
                z[i] = min(r - i + 1, z[i - l]);
            }
            // Try to extend the match beyond the current z[i]
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            // Update [l, r] if we extended past the current r
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    // Find the length of the longest periodic proper prefix
    // A periodic proper prefix is a non-empty prefix (not the whole string)
    // that can be repeated to produce a string starting with s.
    int getLongestPrefix(string &s) {
        vector<int> z = zFunction(s);
        int n = s.length();

        /*
            We iterate backwards because we want the *longest* proper prefix.

            For a prefix of length i to be valid:
            - z[i] == n - i
              This means the substring starting at i matches the first (n-i) characters,
              so the prefix of length i can be repeated to match the suffix.

            Since we search from the end backwards, the first match we find
            will be the longest valid periodic proper prefix.
        */
        for (int i = n - 1; i >= 0; i--) {
            if (z[i] == n - i) {
                return i; // length of the prefix
            }
        }
        return -1; // no periodic proper prefix exists
    }
};

// Given a string s consisting of lowercase English letters, find the maximum possible sum of the lengths of any two non-empty and 
// non-overlapping palindromic substrings of odd length.
// Formally, choose any two substrings s[i...j] and s[k...l] such that 1 ≤ i ≤ j < k ≤ l ≤ s.size(), both substrings are palindromes of odd length, and they do not overlap. Return the maximum sum of their lengths.
// Note: A palindrome is a string that reads the same forward and backward. A substring is a contiguous sequence of characters within the string.
// Class implementing Manacher's algorithm for palindrome lengths
class manachar {
    vector<int> p; // p[i] = radius of palindrome centered at i in the transformed string
public:
    // Constructor: builds the palindrome length array for given string s
    manachar(string s) {
        string t;
        // Convert s into form "#a#b#c#" to handle even/odd palindromes uniformly
        for (auto i : s) {
            t += string("#") + i;
        }
        build(t + "#"); // Add final '#' and build
    }

    // Manacher's algorithm to fill p[]
    void build(string t) {
        int n = t.length();
        p.assign(n, 1); // radius initialized to 1 (center itself)
        int l = 1, r = 1; // current palindrome's left and right boundary in transformed string

        for (int i = 1; i < n; i++) {
            // Mirror trick: try to use previously computed palindrome
            p[i] = max(0, min(r - i, p[l + r - i]));

            // Expand around center i
            while (i + p[i] < n && i - p[i] >= 0 && t[i + p[i]] == t[i - p[i]]) {
                p[i]++;
            }

            // Update current right boundary if palindrome expands beyond it
            if (i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }
    }

    // Returns the longest palindrome length centered at 'cen' in original string
    // odd = true → odd length palindrome; odd = false → even length
    int getLongest(int cen, int odd) {
        // Convert center index in original string to index in transformed string
        int indx = 2 * cen + 1 + !odd;
        // p[indx] stores radius in transformed string, subtract 1 for original length
        return p[indx] - 1;
    }

    // Checks if substring [l, r] is palindrome using precomputed radii
    int is(int l, int r) {
        // If length of [l, r] <= max palindrome length centered at its midpoint, it is palindrome
        if ((r - l + 1) <= getLongest((l + r) / 2, l % 2 == r % 2)) {
            return 1;
        }
        return 0;
    }
};

class Solution {
public:
    int maxSum(string &s) {
        int n = s.length();
        manachar pl(s); // Build Manacher structure

        // left[i] = max odd palindrome length ending at or before i
        // right[i] = max odd palindrome length starting at or after i
        vector<int> left(n, 1), right(n, 1);
        int maxi = 0;

        // Step 1: Fill initial palindrome lengths in left[] and right[]
        for (int i = 0; i < n; i++) {
            int x = pl.getLongest(i, 1); // longest odd palindrome centered at i

            // For left[]: palindrome ends at i + x/2
            int indx = i + x / 2;
            left[indx] = max(left[indx], x);

            // For right[]: palindrome starts at i - x/2
            indx = i - x / 2;
            right[indx] = max(right[indx], x);
        }

        // Step 2: Propagate lengths to cover palindromes ending earlier
        for (int i = n - 2; i >= 0; i--) {
            // If a palindrome of length L ends at i+1, then one of length L-2 ends at i
            left[i] = max(left[i], left[i + 1] - 2);
        }

        // Step 3: Propagate lengths to cover palindromes starting later
        for (int i = 1; i < n; i++) {
            right[i] = max(right[i], right[i - 1] - 2);
        }

        // Step 4: Make left[] store max palindrome length up to index i
        for (int i = 1; i < n; i++) {
            left[i] = max(left[i], left[i - 1]);
        }

        // Step 5: Make right[] store max palindrome length from index i to end
        for (int i = n - 2; i >= 0; i--) {
            right[i] = max(right[i], right[i + 1]);
        }

        // Step 6: Try splitting between every i and i+1
        for (int i = 0; i < n - 1; i++) {
            // Best palindrome in left part + best palindrome in right part
            maxi = max(left[i] + right[i + 1], maxi);
        }

        return maxi; // Maximum sum of two non-overlapping odd palindromes
    }
};

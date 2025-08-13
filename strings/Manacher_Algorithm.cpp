class Manacher {
    vector<int> p; // p[i] = radius of palindrome centered at i in the transformed string
public:
    // Constructor: builds the palindrome length array for given string s
   Manacher(string s) {
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
    int isPalindrome(int l, int r) {
        // If length of [l, r] <= max palindrome length centered at its midpoint, it is palindrome
        if ((r - l + 1) <= getLongest((l + r) / 2, l % 2 == r % 2)) {
            return 1;
        }
        return 0;
    }
}; 

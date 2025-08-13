#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(string &s) {
    int n = s.length();
    vector<int> z(n, 0);

    // [l, r] is the current interval where s[l...r] matches the prefix of s
    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        // If i is inside the current [l, r] match window,
        // we can use previously computed values to initialize z[i]
        if (i <= r) {
            // r - i + 1 = remaining length in the [l, r] window
            // z[i - l] = value from the prefix-aligned position
            z[i] = min(r - i + 1, z[i - l]);
        }

        // Try to extend the match beyond the current z[i]
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        // If we extended the match past r, update [l, r]
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

int main() {
    string s = "abacaba";
    vector<int> z = zFunction(s);

    cout << "Z-array: ";
    for (int val : z) cout << val << " ";
    cout << "\n";

    // Meaning of z[i]:
    // z[i] = length of the longest substring starting at i
    //        that is also a prefix of s.
    // Example for "abacaba":
    // z[4] = 3 means s[0..2] ("aba") == s[4..6] ("aba")
}

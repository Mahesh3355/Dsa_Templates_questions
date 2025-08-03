// You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. 
// You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
// Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
// The cost of the swap is min(basket1[i], basket2[j]).
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.

// Return the minimum cost to make both the baskets equal or -1 if impossible.
using ll = long long;

class Solution {
public:

    // Helper function to compute the excess elements in each basket
    // mp1 and mp2: frequency maps of the two baskets
    // p1 and p2: output vectors to hold the excess elements from each basket
    // Returns 1 if a valid exchange is possible, else 0
    int is_exchange(map<int, int>& mp1, map<int, int>& mp2, vector<int>& p1, vector<int>& p2) {
        for (auto i : mp1) {
            int x = mp1[i.first];
            int y = mp2[i.first];

            // If total count of a fruit is odd, making equal baskets is impossible
            if ((x + y) & 1) return 0;

            int z = (x + y) / 2;

            // Calculate how many extra fruits this basket has
            x -= z;
            y -= z;

            mp1[i.first] = 0;  // Mark as processed
            mp2[i.first] = 0;

            // Store the extra fruits in respective vectors for future swapping
            for (int j = 0; j < x; j++) {
                p1.push_back(i.first);
            }
            for (int j = 0; j < y; j++) {
                p2.push_back(i.first);
            }
        }
        return 1;
    }

    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        ll ans = 0;
        ll mn = 1e9;  // Smallest fruit cost among both baskets
        vector<int> p1, p2;  // Excess elements from basket1 and basket2
        map<int, int> mp1, mp2;

        // Count frequencies and find the minimum value in basket1
        for (auto i : basket1) {
            mp1[i]++;
            mn = min(mn, 1LL * i);
        }

        // Count frequencies and update minimum value in basket2
        for (auto i : basket2) {
            mp2[i]++;
            mn = min(mn, 1LL * i);
        }

        // Check if valid exchange is possible and fill p1, p2 with excess elements
        if (!is_exchange(mp1, mp2, p1, p2) || !is_exchange(mp2, mp1, p2, p1) || p1.size() != p2.size()) {
            return -1;  // Impossible to make baskets equal
        }

        // Sort excess fruits for optimal pairing
        sort(p1.begin(), p1.end());       // from basket1 (ascending)
        sort(p2.begin(), p2.end());       // from basket2 (ascending)
        int i = 0, j = p2.size() - 1;

        // Pair smallest with largest to minimize cost
        while (i < p1.size()) {
            ll y = min(p1[i], p2[j]);
            ll x = min(2 * mn, y);  // Either direct swap or double min cost swap
            ans += x;
            i++, j--;
        }

        return ans;
    }
};

// You are given an integer n and a 2D integer array queries.
// There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.
// queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
// There are no two queries such that queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
// Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    // Helper function: erase all cities in range [l, r) from the set
    void eraseRange(set<int> &cities, int l, int r) {
        auto it1 = cities.lower_bound(l); // first city >= l
        auto it2 = cities.lower_bound(r); // first city >= r
        cities.erase(it1, it2);           // remove all in [l, r)
    }

    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> ans;
        set<int> cities;

        // Step 1: Initially, all cities 0 to n-1 are connected in order
        // Shortest path length = n - 1 edges
        for (int i = 0; i < n; i++) {
            cities.insert(i);
        }

        // Step 2: Process each query
        for (auto &q : queries) {
            int u = q[0], v = q[1];

            /*
               Adding a new road u -> v means we can skip cities
               in range (u, v), i.e. from u+1 up to v-1.
               We remove these cities from the set because
               they will never be part of the shortest path anymore.

               The special query restriction guarantees that
               these "skip ranges" never partially overlap,
               so once a city is removed, it never needs to be restored.
            */
            eraseRange(cities, u + 1, v);

            /*
               The number of edges in the shortest path
               is now: (number of remaining cities - 1)
               because each consecutive city in the set
               is connected directly.
            */
            ans.push_back((int)cities.size() - 1);
        }

        return ans;
    }
};

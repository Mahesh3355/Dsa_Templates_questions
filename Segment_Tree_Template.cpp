#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> tree, data;
    int n;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = data[l];
        } else {
            int mid = (l + r) / 2;
            build(2 * node + 1, l, mid);
            build(2 * node + 2, mid + 1, r);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            data[idx] = val;
            tree[node] = val;
        } else {
            int mid = (l + r) / 2;
            if (idx <= mid)
                update(2 * node + 1, l, mid, idx, val);
            else
                update(2 * node + 2, mid + 1, r, idx, val);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0; // No overlap
        if (ql <= l && r <= qr) return tree[node]; // Total overlap
        int mid = (l + r) / 2;
        int left = query(2 * node + 1, l, mid, ql, qr);
        int right = query(2 * node + 2, mid + 1, r, ql, qr);
        return left + right;
    }

public:
    // Constructor with size and optional initial array
    SegmentTree(int size, const vector<int>& input = {}) {
        n = size;
        data.assign(n, 0);
        tree.assign(4 * n, 0);
        if (!input.empty()) {
            for (int i = 0; i < n && i < input.size(); ++i)
                data[i] = input[i];
        }
        build(0, 0, n - 1);
    }

    void pointUpdate(int idx, int val) {
        if (idx >= 0 && idx < n)
            update(0, 0, n - 1, idx, val);
    }

    int rangeQuery(int l, int r) {
        if (l > r || l < 0 || r >= n) return 0;
        return query(0, 0, n - 1, l, r);
    }
};

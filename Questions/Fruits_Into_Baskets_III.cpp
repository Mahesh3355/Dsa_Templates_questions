// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and 
// baskets[j] represents the capacity of the jth basket.
// From left to right, place the fruits according to these rules:
// Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// Each basket can hold only one type of fruit.
// If a fruit type cannot be placed in any basket, it remains unplaced.
// Return the number of fruit types that remain unplaced after all possible allocations are made.
class SegmentTree {
    int n;
    vector<int> seg;

public:
    // Constructor: Initialize the segment tree array
    SegmentTree(int n) {
        this->n = n;
        seg.assign(4*n+1, 0);
    }

    // Build the segment tree from basket capacities
    void build(int index, int low, int high, vector<int>& baskets) {
        if (low == high) {
            seg[index] = baskets[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, baskets);
        build(2 * index + 2, mid + 1, high, baskets);
        seg[index] = max(seg[2 * index + 1], seg[2 * index + 2]);
    }

    // Find and assign fruit to the leftmost basket that can hold it
    // Returns 1 if assigned, 0 otherwise
    int assignFruit(int index, int low, int high, int fruitQty) {
        // Base case: leaf node
        if (low == high) {
            if (seg[index] >= fruitQty) {
                seg[index] = 0; // Use the basket
                return 1;
            }
            return 0;
        }

        int mid = (low + high) / 2;
        int assigned = 0;

        // Prioritize left child (leftmost basket)
        if (seg[2 * index + 1] >= fruitQty) {
            assigned = assignFruit(2 * index + 1, low, mid, fruitQty);
        }
        else if (seg[2 * index + 2] >= fruitQty) {
            assigned = assignFruit(2 * index + 2, mid + 1, high, fruitQty);
        }

        // Update current node after recursive changes
        seg[index] = max(seg[2 * index + 1], seg[2 * index + 2]);
        return assigned;
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        int unplaced = n;

        SegmentTree sg(n);
        sg.build(0, 0, n - 1, baskets);

        for (int fruitQty : fruits) {
            if (sg.assignFruit(0, 0, n - 1, fruitQty)) {
                unplaced--;
            }
        }

        return unplaced;
    }
};

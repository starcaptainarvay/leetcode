#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename S> ostream& operator<<(ostream& os, const vector<S>& vector) {
    os << "[";

    for (auto element: vector) {
        os << element << " ";
    }

    os << "]";

    return os;
}

/* 
 * You are given an integer array nums of size n and a positive integer k.
 *
 * Divide the array into one or more arrays of size 3 satisfying the following conditions:
 *
 *      Each element of nums should be in exactly one array.    
 *      The difference between any two elements in one array is less than or equal to k.
 *
 * Return a 2D array containing all the arrays. If it is impossible to satisfy the conditions, return an empty array. And if there are multiple answers, return any of them.
*/

class Solution {
    public:
        vector<vector<int>> divideArray(const vector<int>& nums, int k) {
            vector<vector<int>> out = {};
          
            // Shallow copy of input array
            vector<int> sorted = nums;
            sort(sorted.begin(), sorted.end());

            for (auto element: sorted) {
                bool appended = false;

                // Check existing arrays if there's space for the new element
                for (int i=0; i<out.size();i++) {
                    vector<int> array = out[i];

                    if (array.size() < 3) {
                        bool okay = true;

                        for (auto e: array) {
                            //Validate difference
                            if (abs(element - e) > k) {
                                okay = false;
                                break;
                            }
                        }

                        if (okay) {
                            out[i].push_back(element);
                            appended = true;
                            break;
                        }
                    }
                }

                if (!appended) {
                    vector<int> temp = {element};
                    out.push_back(temp);
                }
            }

            // Interrupt result if doesn't meet perfect conditions
            for (auto check: out) {
                if (check.size() < 3) {
                    vector<vector<int>> breakout = {};
                    return breakout;
                }
            }

            return out;
        }
};

int main() {
    Solution* s = new Solution;
    vector<vector<int>> v = s->divideArray({1, 3, 4, 8, 7, 9, 3, 5, 1}, 2);
    
    cout << v << endl;
    return 0;
}

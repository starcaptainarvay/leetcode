#include <iostream>
#include <ios>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

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
        static void count_sort(vector<int>& arr, int n, int power)
        {
            // Initialize output array
            int out[n];
            int i, count[10] = { 0 };

            // Store count of occurrences
            // in count[]
            for (i = 0; i < n; i++)
                count[(arr[i] / power) % 10]++;

            // Change count[i] so that count[i]
            // now contains actual position
            // of this digit in output[]
            for (i = 1; i < 10; i++)
                count[i] += count[i - 1];

            // Build the output array
            for (i = n - 1; i >= 0; i--) {
                out[count[(arr[i] / power) % 10] - 1] = arr[i];
                count[(arr[i] / power) % 10]--;
            }

            // Copy the output array to arr[],
            // so that arr[] now contains sorted
            // numbers according to current digit
            for (i = 0; i < n; i++)
                arr[i] = out[i];
        }

        static void radix_sort(vector<int>& arr) {
            int max = 0;

            for (int i=0;i<arr.size();i++) {
                if (arr[i] > max)
                    max = arr[i];
            }

            for (int exp=1; max/exp > 0; exp*=10) {
                count_sort(arr, arr.size(), exp);
            }
        }

        vector<vector<int>> divideArray(const vector<int>& nums, int k) {
            vector<vector<int>> out = {};

            if (nums.size() % 3 != 0) return out;

            // Shallow copy of input array
            vector<int> sorted(nums);
            Solution::radix_sort(sorted);

            for (int i=0;i<sorted.size();i+=3) {
                vector<int> group = {};

                for (int j=0;j<3;j++) {
                    group.push_back(sorted[i]);
                }

                const int max_diff = abs(group[2] - group[0]); // max difference in group
                if (max_diff > k) {
                    //Interrupt function because result is now invalid
                    out = {};
                    return out;
                } else
                    out.push_back(group);
            }

            return out;
        }
};


int main() {
    Solution* s = new Solution;
    fstream input_data("./data.txt", ios_base::in);
    
    //vector<vector<int>> v = s->divideArray({1, 3, 4, 8, 7, 9, 3, 5, 1}, 2);
    vector<int> input_vector_massive = {};

    int a;
    char comma;
    
    while (input_data >> a) {
        input_vector_massive.push_back(a);
        input_data >> comma;
    }

    getchar();
   
    vector<vector<int>> v = s->divideArray(input_vector_massive, 79610);

    cout << v << endl;
    return 0;
}

/*
why no need         int res = *max_element(right.begin(), right.end());

Why left is enough
left[i] = max subarray ending at i
If you take max(left), you already cover all possible subarrays without deletion

That alone is equivalent to running Kadane’s algorithm.

 */

class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        vector<int> left(n), right(n);

        // max subarray ending at i
        left[0] = arr[0];
        for (int i = 1; i < n; ++i) {
            left[i] = max(arr[i], left[i - 1] + arr[i]);
        }

        // max subarray starting at i
        right[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right[i] = max(arr[i], arr[i] + right[i + 1]);
        }

        int res = *max_element(left.begin(), left.end());

        // try deleting one element
        for (int i = 1; i < n - 1; ++i) {
            res = max(res, left[i - 1] + right[i + 1]);
        }

        return res;
    }
};



class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();

        vector<int>fw(n);
        fw[0] = arr[0];
        int res = arr[0];
        for(int i = 1; i < n; ++i) {
            fw[i] = max(arr[i], fw[i-1] + arr[i]);
            res = max(res,fw[i]);
        }

        vector<int>bw(n);
        bw[n-1] = arr[n-1];
        res = max(res, bw[n-1]);
        for(int i = n -2; i>=0; --i) {
            bw[i] = max(arr[i], arr[i] + bw[i+1]);
            res = max(res, bw[i]);
        }

        for(int i = 1; i < n - 1; ++i) {
            res = max(res, bw[i+1] + fw[i-1]);
        }
        return res;
    }
};
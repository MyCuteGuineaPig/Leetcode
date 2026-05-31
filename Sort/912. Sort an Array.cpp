// Merge Sort

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        auto merge = [&](this auto && merge, int left, int mid, int right ){
            vector<int>tmp(right-left + 1); //no deepcopy entire array 
            for(int i = left; i <= right; ++i) tmp[i-left] = nums[i];
            int l = left; 
            int r = mid+1; 
            int i = left; 
            while (l <= mid || r <= right) {
                if( r > right || l <= mid && tmp[l-left] <= tmp[r-left] ) {
                    nums[i] = tmp[l-left];
                    l++;
                } else {
                    nums[i] = tmp[r-left];
                    r++;
                }
                ++i;
            }
        };

        auto mergeSort = [&](this auto && mergeSort, int left, int right){
            if(left >= right) return;
            int mid = (left + right) / 2;
            mergeSort(left, mid);
            mergeSort(mid+1, right);
            merge(left, mid, right);
        };

        mergeSort(0, nums.size() - 1);
        return nums;
    }
};

//Counting Sort 
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int min_v = *min_element(nums.begin(), nums.end());
        int max_v = *max_element(nums.begin(), nums.end());
        vector<int>vec(max_v - min_v + 1);

        for(auto i: nums) 
            ++vec[i - min_v];
        
        int ind = 0; 
        for(int i = 0; i <vec.size() && ind < nums.size(); ++i ) {
            while(vec[i]) {
                vec[i]--;
                nums[ind++] = i + min_v;
            }
        }
        return nums;
    }
};



//Radix Sort 

class Solution {
public:
    void radixSort(vector<int>& nums) {
        int n = nums.size();
        int max_v = *max_element(nums.begin(), nums.end());

        int exp = 1;

        auto countingSort = [&](int exp) {
            vector<int> cnt(10, 0);
            vector<int> output(n);

            // Count digits
            for (int x : nums) {
                int digit = (x / exp) % 10;
                ++cnt[digit];
            }

            // Prefix sum
            for (int i = 1; i < 10; ++i) {
                cnt[i] += cnt[i - 1];
            }

            // Stable placement
            for (int i = n - 1; i >= 0; --i) {
                int digit = (nums[i] / exp) % 10;
                output[--cnt[digit]] = nums[i];
            }

            nums = output;
        };

        while (max_v / exp > 0) {
            countingSort(exp);
            exp *= 10;
        }
    }

    vector<int> sortArray(vector<int>& nums) {
        vector<int> neg;
        vector<int> pos;

        // Separate negatives and positives
        for (int x : nums) {
            if (x < 0) {
                neg.push_back(-x); // store abs value
            } else {
                pos.push_back(x);
            }
        }

        // Sort both
        if (!neg.empty()) radixSort(neg);
        if (!pos.empty()) radixSort(pos);

        vector<int> result;

        // Negatives should be reversed
        for (int i = neg.size() - 1; i >= 0; --i) {
            result.push_back(-neg[i]);
        }

        // Then positives
        for (int x : pos) {
            result.push_back(x);
        }

        return result;
    }
};
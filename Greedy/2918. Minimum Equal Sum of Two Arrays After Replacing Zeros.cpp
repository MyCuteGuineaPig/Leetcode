class Solution {
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long cnt1 = 0, zero1 = 0;
        for(auto i: nums1){
            cnt1 += i;
            zero1 += (i == 0);
        }
        long long cnt2 = 0, zero2 = 0;
        for(auto i: nums2){
            cnt2 += i;
            zero2 += (i == 0);
        }
        if (zero1 == 0 && zero2 == 0){
            return cnt1 == cnt2 ? cnt1 : -1;
        }
        if(zero1 == 0) {
            return cnt1 >= cnt2 + zero2 ? cnt1: -1;
        }
        if(zero2 == 0) {
            return cnt2 >= cnt1 + zero1 ? cnt2: -1;
        }
        return max(cnt1 + zero1, cnt2 + zero2);
    }
};

class Solution {
public:
    long long minSum(vector<int>& A, vector<int>& B) {
        long long sa = 0, sb = 0, a0 = 0, b0 = 0;
        for (int a: A) {
            a0 += a == 0;
            sa += max(a, 1);
        }
        for (int b: B) {
            b0 += b == 0;
            sb += max(b, 1);
        }
        if (sa < sb && a0 == 0) return -1;
        if (sa > sb && b0 == 0) return -1;
        return max(sa, sb);
    }
};
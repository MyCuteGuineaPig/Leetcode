class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int cnt = 0;
        for(auto i: arr1){
            int l = distance(arr2.begin(), lower_bound(arr2.begin(), arr2.end(), i));
            int left = l != 0 ? arr2[l-1] : numeric_limits<int>::min();
            int right = l != arr2.size() ? arr2[l] : numeric_limits<int>::max();
            //cout<<i<<" left "<<left<<" right "<<right<<endl;
            cnt += left + d < i && right - d > i;
        }
        return cnt;
    }
};

class Solution {
public:
    int findTheDistanceValue(vector<int>& a1, vector<int>& a2, int d) {
        sort(a2.begin(), a2.end());
        int ans = 0;
        for (int i : a1) {
            auto lb = lower_bound(a2.begin(), a2.end(), i - d);
            auto ub = upper_bound(a2.begin(), a2.end(), i + d);
            if (lb == ub)
                ans++;
        }
        return ans;
    }
};


class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        int cnt = 0, i = 0;
        for(int j = 0; i<arr1.size() && j < arr2.size();){
            if (arr1[i] - d > arr2[j]) ++j;
            else 
                cnt += arr1[i++] + d < arr2[j];
        }
        return cnt + arr1.size() - i;
    }
};

class Solution {
public:
    int findTheDistanceValue(vector<int>& a1, vector<int>& a2, int d) {
        sort(a2.begin(), a2.end());
        int ans = 0;
        for (int i : a1) {
            auto lb = lower_bound(a2.begin(), a2.end(), i - d);
            auto ub = upper_bound(a2.begin(), a2.end(), i + d);
            if (lb == ub)
                ans++;
        }
        return ans;
    }
};

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        int idx=0, res=0;
        for(int i=0;i<arr1.size();i++) {
            if(idx>=arr2.size()||arr1[i]<arr2[idx]-d) res++;
            else if(arr1[i]>arr2[idx]+d) idx++, i--;
        }
        return res;
    }
};
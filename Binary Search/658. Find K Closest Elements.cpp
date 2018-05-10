/*
658. Find K Closest Elements
*/

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto left = lower_bound(arr.begin(),arr.end(),x) - arr.begin(), right = left;
        while(k--){
            if(right>=arr.size() || (left>=1 && x-arr[left-1]<=arr[right]-x)) left--; 
            else right++;
        }
        return vector<int>(arr.begin()+left, arr.begin()+right);
    }
};


class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto left = lower_bound(arr.begin(),arr.end(),x) - arr.begin();
        int right = left;
        while(k--){
            //cout<<"before left"<<left<<" right "<<right<<endl;
            if(right>=arr.size() || (left>=1 && x-arr[left-1]<=arr[right]-x)){ //这样可以保证left一定是起点，right一定是最后那个数后面一位
                left--; 
            }else{
                right++;
            }
            //cout<<"left"<<left<<" right "<<right<<endl;
        }
        //if(right<arr.size()) left++, right++;
        //cout<<"left"<<left<<" right "<<right<<endl;
        return vector<int>(arr.begin()+left, arr.begin()+right);
    }
};
/*
   0 1 2 3 4 5 6 7 8 9
  [0,0,1,2,3,3,4,7,7,8]
3
5
before left6 right 7
left5 right 7
before left5 right 7
left4 right 7
before left4 right 7
left4 right 7
left4 right 7

     0 1 2 3 4 5 6 7 8 9 10
    [0,0,0,1,3,5,6,7,8,8]
2
2

before left3 right 4
left2 right 4
before left2 right 4
left2 right 4
left2 right 4

*/

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // vector<int> res(arr);
        // while (res.size() > k) {
        //     if (x - res.front() <= res.back() - x) res.pop_back();
        //     else res.erase(res.begin());
        // }
        // return res;
        
        // binary search
        int left = 0, right = arr.size() - k;
        while (left < right) {
            int mid = (right + left) / 2;
            if (x - arr[mid] > arr[mid + k] - x) left = mid + 1;
            else right = mid;
        }
        vector<int> res(arr.begin() + left, arr.begin() + left + k);
        return res;
    }
};


class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int index = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int i = index - 1, j = index;                                    
        while(k--) (i<0 || (j<arr.size() && abs(arr[i] - x) > abs(arr[j] - x) ))? j++: i--;
        return vector<int>(arr.begin() + i + 1, arr.begin() + j );
    }
};

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto it = lower_bound(arr.begin(),arr.end(),x);
        auto itr = it; it--;
        while(k--) (itr>=arr.end() || (it>=arr.begin() && x-*it <= *itr - x)) ? it--: itr++;
        return vector<int>(it+1,itr);
    }
};
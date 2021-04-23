class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto cmp = [](vector<int>&a, vector<int>&b){
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)>pq(cmp);
        for(auto p: points)
        {
            pq.push(p);
            if(pq.size()>K)
                pq.pop();
        }
        vector<vector<int>>res;
        while(pq.size())
        {
            res.push_back(pq.top());
            pq.pop();
        }
        return res;
    }
};


// Time:  O(n) on average
// Space: O(1)

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        static const auto& dist = [](const vector<int>& v) {
            return v[0] * v[0] + v[1] * v[1];
        };
        nth_element(points.begin(), points.begin() + K, points.end(),
                    [&](const vector<int>& a, const vector<int>& b) {
                        return dist(a) < dist(b);
                    });
        return {points.cbegin(), points.cbegin() + K};
    }
};

// Time:  O(nlogk)
// Space: O(k)
class Solution2 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        static const auto& dist = [](const vector<int>& v) {
            return v[0] * v[0] + v[1] * v[1];
        };
        
        struct Compare {
            bool operator()(const vector<int>& a, const vector<int>& b) {
                return dist(a) < dist(b);
            }
        };
        priority_queue<vector<int>, vector<vector<int>>, Compare> max_heap;
        for (const auto& point : points) {
            max_heap.emplace(point);
            if (max_heap.size() > K) {
                max_heap.pop();
            }
        }
        vector<vector<int>> result;
        while (!max_heap.empty()) {
            result.emplace_back(max_heap.top()), max_heap.pop();
        }
        return result;
    }
};


//Quick-Select
/**
In the quick sort, we will always choose a pivot to compare with other elements. 
After one iteration, we will get an array that all elements smaller than the pivot are on the left side of the pivot and 
all elements greater than the pivot are on the right side of the pviot (assuming we sort the array in ascending order). 
So, inspired from this, each iteration, we choose a pivot and then find the position p the pivot should be. 

Then we compare p with the K, if the p is smaller than the K, 
meaning the all element on the left of the pivot are all proper candidates but it is not adequate, 

we have to do the same thing on right side, and vice versa. 
If the p is exactly equal to the K, meaning that we've found the K-th position. 
Therefore, we just return the first K elements, since they are not greater than the pivot.


Theoretically, the average time complexity is O(N) , but just like quick sort, 

in the worst case, this solution would be degenerated to O(N^2), and pratically, the real time it takes on leetcode is 15ms.

 */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        int l = 0, r = points.size()-1;
        while(l<=r){
            int mid = quickselect(points, l, r);
            if(mid  == K)
                break;
            else if(mid < K)
                l = mid + 1;
            else
                r = mid - 1;
        }
        vector<vector<int>>res;
        for(int i = 0; i<K;++i)
            res.push_back(points[i]);
        return res;
    }
    
    int compare(const vector<int>&a, const vector<int>&b){
        return a[0]*a[0] + a[1]*a[1] - b[0]*b[0] - b[1]*b[1];
    }
  
    int quickselect(vector<vector<int>>& points, int l, int r){
        vector<int> pivot = points[l];
        while(l < r){
            while(l < r && compare(pivot, points[r])<=0) //大于等于pivot 左移
                --r;
            points[l] = points[r];
            while(l < r && compare(pivot, points[l])>=0) //小于等于 pivot 右移
                ++l;
            points[r] = points[l];
        }
        points[l] = pivot;
        return l;
    }

    /* 也可以这么写把pivot 放成left 
    int quickselect(vector<vector<int>>& points, int l, int r){
        vector<int> pivot = points[r];
        while(l < r){
            while(l < r && compare(pivot, points[l])>=0) 
                ++l;
            points[r] = points[l];
            while(l < r && compare(pivot, points[r])<=0)
                --r;
            points[l] = points[r];
            
            
        }
        points[r] = pivot;
        return r;
    }
    
     */
};

/**

QuickSelect [4, 6, 7, 3, 2, 5, 10, 13, 2]
                                                                                                       
l 1 r 8                                                                                                                               
2, 6, 7, 3, 2, 5, 10, 13, 6,                                                                                                           
 
l 2 r 4                                                                                                                               
2, 2, 7, 3, 7, 5, 10, 13, 6,   

l 3 r 3                                                                                                                               
2, 2, 3, 4, 7, 5, 10, 13, 6,  
 */



class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        int l = 0, r = points.size() - 1;
        while (true) {
            int p = partition(points, l, r);
            if (p == K - 1) {
                break;
            }
            if (p < K - 1) {
                l = p + 1;
            } else {
                r = p - 1;
            }
        }
        return vector<vector<int>>(points.begin(), points.begin() + K);
    }
private:
    bool farther(vector<int>& p, vector<int>& q) {
        return p[0] * p[0] + p[1] * p[1] > q[0] * q[0] + q[1] * q[1];
    }
    
    bool closer(vector<int>& p, vector<int>& q) {
        return p[0] * p[0] + p[1] * p[1] < q[0] * q[0] + q[1] * q[1];
    }
    
    int partition(vector<vector<int>>& points, int left, int right) {
        int pivot = left, l = left + 1, r = right; //是left + 1, 把pivot 割除
        while (l <= r) { //必须是 <=,  l == r 点看跟pivot 点比，大的话, --r, 小的话 ++l 
            if (farther(points[l], points[pivot]) && closer(points[r], points[pivot])) {
                swap(points[l++], points[r--]);
            }
            if (!farther(points[l], points[pivot])) {
                l++;
            }
            if (!closer(points[r], points[pivot])) {
                r--;
            }
        }
        swap(points[pivot], points[r]); //l 可能大于point.size(), 因为可能所有点都小于0， 但r 不会小于0，因为pivot是起点 被隔开
        return r;
    }
    /* or 可以这么写
    int partition(vector<vector<int>>& points, int left, int right) {
        int pivot = left, l = left+1, r = right;
        while (l <= r) {
            while (l<= r && farther(points[l], points[pivot]) && closer(points[r], points[pivot])) {
                swap(points[l++], points[r--]);
            }
            while (l <= r && !farther(points[l], points[pivot])) {
                l++;
            }
            while (l<= r && !closer(points[r], points[pivot])) {
                r--;
            }
        }
        swap(points[pivot], points[r]);
        return r;
    }
    
    也可以换顺序
    int partition(vector<vector<int>>& points, int left, int right) {
        int pivot = left, l = left + 1, r = right;
        while (l <= r) { 
            if (!farther(points[l], points[pivot])) {
                l++;
            }
            if (!closer(points[r], points[pivot])) {
                r--;
            }
            if (farther(points[l], points[pivot]) && closer(points[r], points[pivot])) {
                swap(points[l++], points[r--]);
            }
            
        }
        swap(points[pivot], points[r]); 
        return r;
    }
    
     */
};


//multiset
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        multiset<vector<int>, compare> mset;
        for (vector<int>& point : points) {
            mset.insert(point);
            if (mset.size() > K) {
                mset.erase(mset.begin());
            }
        }
        vector<vector<int>> ans;
        copy_n(mset.begin(), K, back_inserter(ans));
        return ans;
    }
private:
    struct compare {
        bool operator()(const vector<int>& p, const vector<int>& q) const {
            return p[0] * p[0] + p[1] * p[1] > q[0] * q[0] + q[1] * q[1];
        }
    };
};

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        multiset<vector<int>, compare> mset(points.begin(), points.end());
        vector<vector<int>> ans;
        copy_n(mset.begin(), K, back_inserter(ans));
        return ans;
    }
private:
    struct compare {
        bool operator()(const vector<int>& p, const vector<int>& q) const {
            return p[0] * p[0] + p[1] * p[1] < q[0] * q[0] + q[1] * q[1];
        }
    };
};

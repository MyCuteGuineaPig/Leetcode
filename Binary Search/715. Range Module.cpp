class RangeModule {
public:
    map<int,int> mp;
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {        
        auto it = mp.lower_bound(left);
        auto it2 = mp.upper_bound(right);
        if (it == mp.begin()){
            if (it2 == mp.begin()){
                mp[left] = right;
            } else {
                mp[left] = max(right, prev(it2)->second);
            }
        } else if(it != mp.begin()){
             if(prev(it)->second < left){
                mp[left] = max(right, prev(it2)->second);
             } else {
                prev(it)->second = max(right, prev(it2)->second);
             }
        } 

        removeIntervals(left+1, right);
    }
    
    bool queryRange(int left, int right) {
        auto it = mp.upper_bound(left);
        if(it != mp.begin()){
            it = prev(it);
        }
        return it != mp.end() && it->first <= left && it->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it2 = mp.lower_bound(right);
        if(it2 != mp.begin() && prev(it2)->second > right) {
            mp[right] = prev(it2)->second;
        }

        auto it = mp.lower_bound(left); //必须declare here因为mp[right] 会改变iterator
        if(it != mp.begin() && prev(it)->second > left) { //必须后弄, 因为it1 可能等于it2
            prev(it)->second = left;
        }
        removeIntervals(left, right-1);
    }

    int removeIntervals(int l, int r){ //remove all intervals which between l and r
        for(auto it = mp.lower_bound(l); it!=mp.end() && r >= it->first; ){
            it = mp.erase(it);
        }
        return r;
    }
};





class RangeModule {
public:
    map<int,int> mp;
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        auto it = mp.lower_bound(left);
        if(it != mp.begin() && prev(it)->second >=left){ // e.g [1, 10) left = 10
            left = prev(it)->first;
        }
        mp[left] = removeIntervals(left, right);
    }
    
    bool queryRange(int left, int right) {
        auto it = mp.upper_bound(left);
        if(it != mp.begin()){
            it = prev(it);
        }
        return it != mp.end() && it->first <= left && it->second >= right;
    }
    
    void removeRange(int left, int right) {
        int r1 = removeIntervals(left, right);
        auto it = mp.lower_bound(left);
        
        if (it != mp.begin() && prev(it)->second >left) {
            r1 = max(r1, prev(it)->second ); //比如 map = [10,20], left = 14, right = 16, r1 return from removeIntervals 是16, 现在更新到20
            prev(it)->second = left;
            
        }
        if (r1 > right){
            mp[right] = r1;
        }
    }

    int removeIntervals(int l, int r){ //remove all intervals which between l and r
        for(auto it = mp.lower_bound(l); it!=mp.end() && r >= it->first; ){
            //r >= it->first 在区间里面
            r = max(r, it->second);
            it = mp.erase(it);
        }
        return r;
    }
};


/*

You'll notice self.track is always an array with even number of elements.
Let's say we have [1,3,9,11], which denotes intervals [1,3), [9,11). say we want to add [4,6) to the ranges, 
bisect_left([1,3,9,11], 4) will return 2,
 which is an even index. This means the 4 does not overlap with any of the intervals [1,3) and [9,11) 
therefore we would need to add the interval to the final result.
On the other hand, if we were to add the interval [3, 6), bisect_left([1,3,9,11), 3) will return 1, 
this means 3 is overlapping with an existing interval and we do not have to add it to the final result.


          range, lft,  rgt
add  1 3 [1, 3] 0 0
add  9 11 [1, 3, 9, 11] 2 2
add  3 6 [1, 6, 9, 11] 1 2
add  4 10 [1, 11] 1 3,  表示4 和10 都是两个区间中间

https://leetcode.com/problems/range-module/solutions/244194/python-solution-using-bisect-left-bisect-right-with-explanation/
*/
class RangeModule {
public:
    vector<int> range;
    RangeModule() {
    }
    
    void addRange(int left, int right) {
        int lft = lower_bound(range.begin(), range.end(), left) - range.begin();
        int rgt = upper_bound(range.begin(), range.end(), right) - range.begin();
        
        vector<int> cur;
        if (lft % 2 == 0) cur.push_back(left);
        if (rgt % 2 == 0) cur.push_back(right);
        
        range.erase(lft + range.begin(), rgt + range.begin());
        range.insert(lft + range.begin(), cur.begin(), cur.end());
    }
    
    bool queryRange(int left, int right) {
        int lft = upper_bound(range.begin(), range.end(), left) - range.begin();
        int rgt = lower_bound(range.begin(), range.end(), right) - range.begin();
        return (lft == rgt && lft % 2 == 1);
    }
    
    void removeRange(int left, int right) {
        int lft = lower_bound(range.begin(), range.end(), left) - range.begin();
        int rgt = upper_bound(range.begin(), range.end(), right) - range.begin();
        
        vector<int> cur;
        if (lft % 2 == 1) cur.push_back(left);
        if (rgt % 2 == 1) cur.push_back(right);
        
        range.erase(lft + range.begin(), rgt + range.begin());
        range.insert(lft + range.begin(), cur.begin(), cur.end());
        
    }
};




class RangeModule {
public:
    map<int, int>mp;
    RangeModule() {  
    }
    
    void addRange(int left, int right) {
        auto it1 = mp.upper_bound(left);
        if(it1 != mp.begin() && prev(it1)->second >= left){
            left = prev(it1)->first;
            right = max(right, prev(it1)->second);
            mp.erase(prev(it1));
        }
        while(it1!= mp.end() && it1->first <= right){
            right = max(right, it1->second);
            it1 = mp.erase(it1);
        }
        mp[left] = right;
    }
    
    bool queryRange(int left, int right) {
        auto it1 = mp.upper_bound(left);
        if (it1 != mp.begin()) {
            it1 = prev(it1);
        }
        return it1->first <= left && it1->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = mp.upper_bound(left);

        if(it!= mp.begin() && prev(it)->second > left){
            int org_right = prev(it)->second;
            prev(it)->second = left;
            if(org_right > right){
                auto cur = mp.insert({right, org_right});
                return;
            }
        }
        else if(it!= mp.end() && it->first == left) {
            int org_right = prev(it)->second;
            it = mp.erase(it);
            if(org_right > right){
                auto cur = mp.insert({right, org_right});
                return;
            }
        }
        while(it != mp.end() && right > it->first){
            int org_right = it->second;
            it = mp.erase(it);
            if (org_right > right){
                auto cur = mp.insert({right, org_right});
                it = cur.first; 
                break;
            }
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

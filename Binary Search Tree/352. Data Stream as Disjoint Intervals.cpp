/*
352. Data Stream as Disjoint Intervals

Given a data stream input of non-negative integers a1, a2, ..., an, ..., 
summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?

*/
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {}
    vector<Interval> vec;
    
    void addNum(int val) {
        auto cmp = [](Interval a, Interval b){return a.start<b.start;};
        auto it = lower_bound(vec.begin(),vec.end(),Interval(val, val), cmp);
        if (it!=vec.begin() && (it-1)->end >= val-1) it--;
        int start = val, end = val;
        while(it!=vec.end() && val+1>=it->start && val-1<=it->end){
            """
            比如 1,3,7,2 结果是[1,3],[7,7], 但是[1,4,7,2] 结果是[1,2],[4,4],[7,7]
            2+1 >= 1 && 2-1 < = 1
            2 + 1>=3 && 2-1 <= 3
            """

            start = min(start, it->start);
            end = max(end, it->end);
            it = vec.erase(it);
        }
            
        vec.insert(it,Interval(start, end));
    }
    
    vector<Interval> getIntervals() {
        return vec;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */


class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {}
    vector<Interval> vec;
    
    void addNum(int val) {
        auto cmp = [](Interval a, Interval b){return a.start<b.start;};
        auto it = lower_bound(vec.begin(),vec.end(),Interval(val, val), cmp);
        if (it!=vec.begin() && (it-1)->end >= val-1) it--;
        int start = val, end = val;
        while(it!=vec.end() && end+1>=it->start){
            start = min(start, it->start);
            end = max(end, it->end);
            it = vec.erase(it);
        }
            
        vec.insert(it,Interval(start, end));
    }
    
    vector<Interval> getIntervals() {
        return vec;
    }
};


/*

using Set
*/



class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {}
    
    void addNum(int val) {
        auto it = st.lower_bound(Interval(val, val));
        if (it!=st.begin() && (--it)->end < val-1) it++;
        int start = val, end = val;
        while(it!=st.end() && val+1>=it->start && val-1<=it->end){
            start = min(start, it->start);
            end = max(end, it->end);
            it = st.erase(it);
        }
            
        st.insert(it,Interval(start, end));
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> vec;
        for(auto i: st){
            vec.push_back({i.start,i.end});
        }
        return vec;
    }
    
    struct Cmp{
        bool operator()(Interval a, Interval b){ return a.start < b.start; }
    };
    set<Interval, Cmp> st;
};




// Time:  addNum: O(logs), getIntervals: O(s), s is the data stream's size.
// Space: O(s)
class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        nums_.emplace(val);
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> result;
        if (nums_.empty()) {
            return result;
        }
        auto start = *nums_.begin(), end = *nums_.begin();
        for (auto it = next(nums_.begin()); it != nums_.end(); ++it) {
            if ( *it == end + 1) {
                end = *it;
            } else  {
                result.emplace_back(start, end);
                if (it != nums_.end()) {
                    start = end = *it;
                }
            }
        }
        result.emplace_back(start, end);
        return result;
    }

private:
    set<int> nums_;
};


/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
public:
    void addNum(int val) {
        auto Cmp = [](Interval a, Interval b) { return a.start < b.start; };
        auto it = lower_bound(vec.begin(), vec.end(), Interval(val, val), Cmp);
        int start = val, end = val;
        if (it!=vec.end()) 
            cout<<(it->start)<< "  end  "<<(it->end)<<endl;
        if(it != vec.begin() && (it-1)->end+1 >= val) {
            cout<<"  it -- "<<" (it-1)->end "<<(it-1)->end<<"  val "<<val<<endl;
            it--;
        }
        while(it != vec.end() && val+1 >= it->start && val-1 <= it->end) 
        //比如 1,3,7,2 结果是[1,3],[7,7], 但是[1,4,7,2] 结果是[1,2],[4,4],[7,7]
        {
            cout<<" val "<<val<<" start "<<start<< " it->start "<<it->start<<" end "<<end<<" it->>edn "<<it->end<<endl;
            start = min(start, it->start);
            end = max(end, it->end);
            it = vec.erase(it);
            cout<<" after start "<<start<<" end "<<end<<endl;
        }
        cout<<" insert "<<val<<" start "<<start<<" end "<<end<<endl;
        vec.insert(it,Interval(start, end));
    }
    
    vector<Interval> getIntervals() {
        return vec;
    }
private:
    vector<Interval> vec;
};
/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */

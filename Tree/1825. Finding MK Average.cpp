
/*
BIT Tree
*/
class MKAverage {
private:
    class BITtree{
        private:
            vector<long>sums;
            int n;
        public:
            BITtree(int n_): n(n_) { sums.resize(n+1, 0);}
            
            void add(int index, int val){
                while(index <= n){
                    sums[index] += val;
                    index += index & (-index);
                }
            }
        
            long getSum(int index){
                long tot = 0;
                while(index){
                    tot += sums[index];
                    index &= index - 1;
                }
                return tot;
            }
    };
    
    BITtree value;
    BITtree index;
    queue<int>q;
    int m; 
    int k;
    
    int getIndex(int need){
        int l = 1, r = 100000;
        while(l < r){
            int mid = (l + r) / 2;
            if(index.getSum(mid) < need)
                l = mid + 1;
            else r = mid;
        }
        return l;
    }
    
public:
    MKAverage(int m, int k): m(m), k(k), value(100001), index(100001) {
    }
    
    void addElement(int num) {
        q.push(num);
        if(q.size() == m+1){
            int last = q.front(); q.pop();
            value.add(last, -last);
            index.add(last, -1);
        }
        value.add(num, num);
        index.add(num, 1);
    }
    
    int calculateMKAverage() {
        if(q.size() < m)return -1;
        int lo = getIndex(k), hi =getIndex(m-k); 
        long long tot = value.getSum(hi) - value.getSum(lo); //没有算上lo的数
        //比如[5,5,5,5,5], m=5, k =1, lo = 5, high = 5, tot = 0
        tot += (index.getSum(lo) - k)*lo; 
        //加上lo 少算的，没有算上重复的数, (5-1)*5 = 20, 因为lo 是至少拥有k的数的，可能含有边界值
        tot -= (index.getSum(hi) - (m-k))*hi; //除去多算的 (5 - （5-1))*5 = 1*5 = 20
        // 因为high 是至少拥有k的数的，可能算多了边界值
        return tot / (m - 2*k);
    }
    

};


/*
Three Multiset
 Time: 
     MKAverage: O(1)
     addElement: O(logM)
     calculateMKAverage: O(1)
 Space: O(M)
*/
class MKAverage {
public:
    MKAverage(int m, int k): m(m), k(k) {
        
    }
    
    void addElement(int num) {
        q.push(num);
        if(q.size() > m){
            erase(q.front());
            q.pop();
        }
        add(num);
    }
    
    int calculateMKAverage() {
        if(q.size() < m)
            return -1;
        return tot / (m - 2*k);
    }
    
    void add(int val){
       left.insert(val);
       if(left.size() > k){
           middle.insert(*left.rbegin());
           tot += *left.rbegin();
           left.erase(prev(left.end()));
       }
       if(middle.size() > m - 2*k){
           right.insert(*middle.rbegin());
           tot -= *middle.rbegin();
           middle.erase(prev(middle.end()));
       }
    }
    
    void erase(int val){
        if(left.count(val)){
            auto it = left.find(val);
            left.erase(it);
        }
        else if(middle.count(val)){
            auto it = middle.find(val);
            tot -= *it;
            middle.erase(it);
        }else{
            auto it = right.find(val);
            right.erase(it);
        }
        
        if(left.size() < k){
            left.insert(*middle.begin());
            tot -= *middle.begin();
            middle.erase(middle.begin());
        }
        
        if(middle.size() < (m - 2*k)){
            middle.insert(*right.begin());
            tot += *right.begin();
            right.erase(right.begin());
        }

    }
    
    queue<int>q;
    multiset<int>left, middle, right;
    long tot = 0;
    int m;
    int k;
};
/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */

class MKAverage {
public:
    int m = 0, k = 0, sz = 0, pos = 0;
    long sum = 0;
    vector<int> v;
    multiset<int> left, mid, right;
    void remove(int n) {
        if (n <= *rbegin(left))
            left.erase(left.find(n));
        else if (n <= *rbegin(mid)) {
        auto it = mid.find(n); 
        sum -= *it;
        mid.erase(it);
        }
        else
            right.erase(right.find(n));
        if (left.size() < k) {
            left.insert(*begin(mid));
            sum -= *begin(mid);
            mid.erase(begin(mid));
        }
        if (mid.size() < sz) {
            mid.insert(*begin(right));
            sum += *begin(right);
            right.erase(begin(right));
        }
    }
    void add(int n) {
        left.insert(n);
        if (left.size() > k) {
            auto it = prev(end(left));
            mid.insert(*it);
            sum += *it;
            left.erase(it);
        }
        if (mid.size() > sz) {
            auto it = prev(end(mid));
            sum -= *it;
            right.insert(*it);
            mid.erase(it);
        }
    }
    MKAverage(int m, int k) : m(m), k(k), sz(m - 2 * k) {
        v = vector<int>(m);
    }
    void addElement(int num) {
        if (pos >= m)
            remove(v[pos % m]);
        add(num);
        v[pos++ % m] = num;
    }
    int calculateMKAverage() {
        if (pos < m)
            return -1;
        return sum / sz;
    }
};


/*
sort A, B 
如果 A[i] > B[j], 把A[i] 放前面放
否则 把A[i] 放在末尾，配给最大的B 
*/
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        vector<pair<int,int>>Bs;
        for(int i = 0; i<B.size(); i++) Bs.push_back({B[i], i});
        sort(Bs.begin(), Bs.end()); sort(A.begin(), A.end());
        vector<int>res(B.size());
        for(int i = 0, jstart = 0, jend = A.size()-1; i<A.size(); i++){
            if(A[i]>Bs[jstart].first) res[Bs[jstart++].second] = A[i];
            else res[Bs[jend--].second] = A[i];  //最小的A 给当前最大的 B
        }
        return res;
    }
};


/*
maxheap
Priority queue: push 进 B 和B的index，top的是B的当前最大值
A用两个pointer, 初始化lo = 0， hi = n-1

如果当前A[hi] > B, A满足当前值 给 B的index assign A[hi]: res[idx] = A[hi--]
else B不能被满足，放上最小的值给B: res[idx] = A[lo++]

*/
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        priority_queue<pair<int,int>>pq;
        for(int i = 0; i<B.size(); i++) pq.push({B[i], i});
        sort(A.begin(), A.end());
        vector<int>res(B.size());
        int lo = 0, hi = A.size()-1;
        
        while(!pq.empty()){
            auto b = pq.top(); pq.pop();
            if(A[hi]>b.first) res[b.second] = A[hi--];
            else res[b.second] = A[lo++]; //最小的A 给当前最大的 B
        }
        
        return res;
    }
};

/*
minheap:
multiset: 只把Apush进 heap
loop B: 如果当前heap 最大的(r.begin())比 B还小， 把当前最小的给现在 res[ind] = heap.top() 
        else: 用upper_bound找当前仅比B大一点的

*/

class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        multiset<int>pq(begin(A), end(A));
        vector<int>res;
        for(auto b: B){
            auto p = *pq.rbegin() <= b ? pq.begin() : pq.upper_bound(b);
            res.push_back(*p);
            pq.erase(p);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> advantageCount(vector<int> A, vector<int> B) {
        map<int, int> m;
        for (int i : A) m[i]++;
        map<int,int>::iterator it;
        vector<int> res;
        for (int i : B) {
            it = m.upper_bound(i);
            int x = it != m.end() ? it->first : m.begin()->first;
            if (--m[x] == 0) m.erase(x);
            res.push_back(x);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        vector<int> sortedA(A.cbegin(), A.cend());
        sort(sortedA.begin(), sortedA.end());
        vector<int> sortedB(B.cbegin(), B.cend());
        sort(sortedB.begin(), sortedB.end());

        unordered_map<int, vector<int>> candidates; //有可能B是重复的，比如B = [1,12,12]
        vector<int> others;
        int j = 0;
        for (const auto& a : sortedA) {
            if (a > sortedB[j]) { //当前A可以匹配当前B，push 进result
                candidates[sortedB[j]].emplace_back(a);  
                ++j;
            } else {
                others.emplace_back(a); //a小了，++a; 
            }
        }
        vector<int> result;
        for (const auto& b : B) {
            if (!candidates[b].empty()) {
                result.emplace_back(candidates[b].back());
                candidates[b].pop_back();
            } else {
                result.emplace_back(others.back());
                others.pop_back();
            }
        }
        return result;
    }
};


class Solution 
{
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) 
    {
        sort(A.begin(), A.end());
        vector<int> res(B.size(), -1);
        for (int i = 0 ; i < B.size() ; ++i)
        {
            const auto pos = upper_bound(A.begin(), A.end(), B[i]);
            if (pos != A.end())
            {
                res[i] = *pos;
                A.erase(pos);
            }
        }
        for (int i = 0; i < B.size(); ++i)
        {
            if (res[i] == -1)
            {
                res[i] = A[A.size() - 1];
                A.pop_back();
            }
        }
        return res;
    }
};
/*

659. Split Array into Consecutive Subsequences


/*
pre: 上一个process的数
p1:  以pre结尾长度为1 的数列   pre = 4, seq = 4
p2:  以pre结尾长度为2 的数列   pre = 4, seq = [3,4]
p2:  以pre结尾长度大于等于3 的数列, pre = 4, seq = [1,2,3,4]

cur: 现在将要process 的数
c1:  以cur结尾长度为1 的数列
c2:  以cur结尾长度为2 的数列
c3:  以cur结尾长度大于等于3 的数列
cnt: cur 在数列中出现的个数

遇到cur, 分两种情况讨论,  
1. cur != pre + 1, 表示cur 不能加到以pre结尾 consecutive subsequence, 因为之前p1 == 0 && p2 必须为0，
    否则return false,  接下来c1 = cnt, c2 = 0, c3 =0; 我们仅有以cur开始的长度为1的subsequence

2. cur == pre + 1; 这时候我们处理的顺序，应该先把cur分给长度为1，再分给长度为2，再分给长度为3个，
   我们先看是不是cnt >= p1 + p2, 如果不是的话，代表现在的cur不够分给之前长度为1，长度为2的(之前有的subsequnce长度不够3)，return false
   此时： 我们已经知道 cur肯定够分给p1, p2
   如果分给 p1, p2 , p3之后，还富余，就给新的c1;  c1 = max(0, cnt - (p1 + p2 + p3));  
   c2 = p1, （cnt>p1+ p2)
   c3 = p2 + min(p3, cnt-(p1+p2));  
   min(p3, cnt - (p1 + p2)), 可能cnt - (p1 + p2) 大于p3, 表示p3不能接住所有的剩下的， cnt > p1 + p2 + p3, 
   所以我们只保留之前已经长度是3的个数,  比如[1,2,3], [1,2,3],[1,2,3], 4,4,4,4
   还有可能， cnt - (p1 + p2) < p3, 表示p3， 之前可以在上一位结束一部分，不必所有的p3都延续一位
   比如 【1，2，3], [1,2,3], [1,2,3], cur = 4, 4， 只需两个p3接住4，另外一个p3在pre结束，[1,2,3,4], [1,2,3,4], [1,2,3]
*/

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int p1 = 0, p2 =0, p3=0, c1 = 0, c2 = 0, c3 = 0, pre=INT_MAX, cur = 0, cnt = 0;
        for(int i = 0; i<nums.size(); p1=c1, p2=c2, p3=c3,pre=cur){
            for(cur = nums[i], cnt = 0; i<nums.size() && cur == nums[i]; i++, cnt++);
            
            if(cur!=pre+1){
                if(p1!=0 || p2!=0 ) return false; // 比如pre = 3 , cur =5, 之前到3为止，长度为1，长度为2的array必须是0
                c1 = cnt; c2 = 0; c3 = 0;
            }else if(cur == pre+1){
                if(cnt < p1 + p2) //有些长度是1，2的array不能填满，返回false
                    return false;
                c1 = max(0, cnt - (p1 + p2 + p3));
                c2 = p1;
                c3 = p2 + min(p3, cnt-(p1+p2)); //cnt-(p1+p2) 分给p1, p2 之后还剩下 cnt - p1 - p2, 
                //可以分给p3,但是要保证p3 够多接的住，比如[1,2,3], [1,2,3],[1,2,3], 4,4,4,4 有4个剩余的
                // 3 只能接住3个， 多的一个只能给4 
                
            }
        }
        
        return p1 == 0 && p2 == 0;
    }
};





/*
Solution 2: 
cnt 表示后面还有几个i还没被使用，tail在i点，以i点为结尾且长度大于等于3的sequence 的个数

当碰到i，
1. 先看cnt是不是大于0，小于0表示i已经被提前透支完了
2. 如果有，看有没有以i-1结尾的且长度大于3等于的, 如果有就继续这个sequence，
    - 当然我们也可以用i点再开始新的sequence，但是append old sequence i-1 should always work
     比如 [1,2,3,4,5], 在4点，我们可以append 4, 让新的sequence 变成[1,2,3,4], 但是假如我们想开启新的sequence 发现没有4+2
3. 如果没有i-1结尾的， 看能不能以i开头建立新的sequence，建立新的sequence前提是
    i+1， i+2 没有预支完， cnt[i+1] > 0 && cnt[i+2] >0

不能调换2，3的顺序，比如例子： [1,2,3,4,5,5,6,7]
正确的sequence是 (1,2,3,4,5), (5,6,7)
如果一碰到点先考虑 建立新的sequence，到4点，建立新的sequence (1,2,3), (4,5,6), 发现只有5，7点了，会return false

*/

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int,int>cnt, tail;
        for(auto i: nums) cnt[i]++;
        for(auto i: nums){
            if(cnt[i] == 0) continue; //提起被支付了，已经在sequence里面了，继续
            cnt[i]--;
            if(tail[i-1]){
                tail[i-1]--;
                tail[i]++;
            }else if(cnt[i+1] && cnt[i+2]){
                cnt[i+1]--;
                cnt[i+2]--;
                tail[i+2]++;
            }
            else return false;   
        }
        return true;
    }
};

/*

Solution 3: check 每三个数构成sequence
*/
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int base = nums[0];
        for(auto &i: nums) i-=base; //第一个数0，之后跟原来第一个数比
        
        unordered_map<int,int>cnt;
        for(auto i: nums) cnt[i]++;
        
        for(int i = 2; i<=nums.back()+2;i++){ //最大的数+2， 因为比如数[0], 1只有到2的时候可以查出来
            int cur = cnt[i];  //现在i这个数
            int one = max(cnt[i-1] - cnt[i-2], 0);//以i-1 开头数
            int two = max(cnt[i-2] - cnt[i-3], 0);//以i-2 开头的数
            if(cur < one + two || cnt[i- 1] < two) return false; 
            // cnt < p1 + p2 (cur<one+two) 
            //cnt[i- 1] < two 原理上也可以用 cur < one 代替，但是我们从 i = 2开始的，如果用cur < one 代替，比如[0, 2,3,4]的0就查不出了
        }
        return true;
    }
};

/*
priority_queue

Case 1 : num == pq.peek().end, we offer a new interval (num, num) to pq => #1
Case 2 : num == pq.peek().end+ 1, we poll a interval prev, offer a new interval (prev.start, num) => #2
Case 3 : num > p1.peek().end + 1,
we keep abandoning intervals (if the length of the interval to abandon is smaller than 3, return false) until we could reduce to case 1 or case 2 => #3

The order of 3 cases above matters. For easier implementation, Case 3 should be checked first.

In the priority queue, all intervals are sorted by end increasingly, if there is a tie, we sort them by size increasingly.



priority_queue:
1. 如果end 一样，返回长度短的
2. 如果end 不一样，返回end 小的

[1,2,3,3,4,4,5,5], 
 
 到第一个4的时候, pq 有 [1,3], [3,3], 先用[3,3]
到第二个4的时候, pq 有[1,3], [3,4],  先用[1,3]
 */

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        auto cmp = [](vector<int>&a, vector<int>&b){
          if(a[1] == b[1] )
              return (a[1] - a[0]) > (b[1] - b[0]);  //如果end 一样，先return 长度短的
          return a[1] > b[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)>pq(cmp);
        for(auto num: nums){
            while(pq.size() && pq.top()[1] + 1 < num){
                if(pq.top()[1] - pq.top()[0] < 2)
                    return false;
                pq.pop();
            }
            if(pq.empty() || pq.top()[1] == num)
                pq.push({num, num});
            else{ // pq.top()[1] + 1 =  num
                vector<int> top = pq.top(); 
                pq.pop();
                top[1] = num;
                pq.push(top);
            }
        }
        while(pq.size()){
            if(pq.top()[1] - pq.top()[0] < 2)
                return false;
            pq.pop();
        }
        return true;
    }
};
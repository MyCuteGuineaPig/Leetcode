/*
846. Hand of Straights


Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.

Return true if and only if she can.

 

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.
 

Note:

1 <= hand.length <= 10000
0 <= hand[i] <= 10^9
1 <= W <= hand.length

*/



class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        if(hand.size()%W) return false;
        multiset<int>minheap(hand.begin(),hand.end());
        while(minheap.size()){
            int top = *minheap.begin();
            minheap.erase(minheap.begin());
            for(int i = 1; i<W;i++){
                auto it = minheap.find(top+i);
                if(it == minheap.end()) return false;
                minheap.erase(it);
            }
        }
        return true;
    }
};


//O(MlogM + MW)
class Solution {
public:
    bool isNStraightHand(vector<int> hand, int W) {
        map<int, int> c;
        for (int i : hand) c[i]++;
        for (auto it : c)
            if (c[it.first] > 0)
                for (int i = W - 1; i >= 0; --i)
                    if ((c[it.first + i] -= c[it.first]) < 0)
                        return false;
        return true;
    }
};


class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        if (hand.size() % W) {
            return false;
        }

        unordered_map<int, int> counts;
        for (const auto& i : hand) {
            ++counts[i];
        }

        priority_queue<int, vector<int>, greater<int>> min_heap(hand.begin(), hand.end());
        for (int i = 0; i < hand.size() / W; ++i) {
            while (counts[min_heap.top()] == 0) {
                min_heap.pop();
            }
            int start = min_heap.top(); min_heap.pop();
            for (int j = 0; j < W; ++j) {
                --counts[start];
                if (counts[start] < 0) {
                    return false;
                }
                ++start;
            }
        }
        return true;
    }
};


/*

上面方法对有的例子比较慢: 

比如 w=3  map为[2:2], [3:3], [4:4], [5:2],[6:1],  需要loop 三次, start 分别为2,3,4 但是下面方法不需要loop 三次, instead 一次就够了

Explanation:

Count number of different cards to a map c
open 记录此刻在open的interval
In a queue start, 记录每个key新建的interval，以这个点开始的interval  = open - c[key]
Loop from the smallest card number.
For example, hand = [1,2,3,2,3,4], W = 3
We meet one 1:
opened = 0, queue = {1}, newopen = 1
We meet two 2:
opened = 1, queue = {1,1}, new_open = 2
We meet two 3:
oepn = 2, queue = {1,1,0}, new_open = 1 (因为1要结束, open = 2-1(queue.front )) 
We meet one 4:
opened = 1,  queue = {1,0,0}, new_open = 0 因为2要结束, open = 1 -1 (queue.front )
return if no more open groups.


Complexity: O(MlogM), where M is the number of different cards.



*/
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        if(hand.size()%W) return false;
        map<int,int>c;
        for(auto i: hand) c[i]++;
        int last = -1, open = 0;
        queue<int>newopen_queue;
        for(auto i: c){
            int key = i.first;
            if(open > 0 && key>last+1 || open > i.second){
                return false;
            }
            newopen_queue.push(i.second-open);
            open = i.second; last = key;
            if(newopen_queue.size() == W){
                open -= newopen_queue.front();
                newopen_queue.pop();
            }
        }
        return open == 0;
    }
};



//self

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        int size = hand.size();
        if(size % W != 0) return false;
        int batch = size / W;
        map<int,int>mp;
        for(auto i: hand) ++mp[i];
        while(!mp.empty()){
            int start = mp.begin()->first, count = mp.begin()->second;
            for(int y = 0; y<W; ++y)
            {
                mp[start + y] -= count;
                if(mp[start+y]<0) 
                    return false;
                if(mp[start+y] == 0)
                    mp.erase(start+y);
            }
        }
        return true;
    }
};

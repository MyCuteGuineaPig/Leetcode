ps://leetcode.com/problems/maximum-length-of-pair-chain/description/


/*
根据end sort：

因为chain是要 下一个点的start > 上一个点的end，所以end由小到大sort，end逐渐增大，有利于一开始减小end, 可以放进更小的start，增加count

不用管start的position,因为不管start，只要start > end就可以加起来，否则免谈
比如 当前end = 3, 后面有点[2,6], [4,6], 如果[2,6]在前面，2 < 3; start < end, 不能加; 碰见[4,6] start >end; count + 1
                比如[4,6] 先出现 start > end, count + 1, 再[2,6] 还是不能加;
            还因为两个点的end 都是一样，所以不论谁，如果是end = 3; [4,6], [5,6]都只能加一个

*/
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>&a, const vector<int>&b){return a[1]<b[1];});
        long end = numeric_limits<long>::min() ; int count = 0;
        for(auto p: pairs)
            if(p[0]>end)
                end = p[1], count++;
        return count;
    }
};

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](vector<int>&a, vector<int>&b){return a[1] < b[1];});
        int count = 0, i = 0, n = pairs.size();
        while (i < n) {
            count++;
            int curEnd = pairs[i][1];
            while (i < n && pairs[i][0] <= curEnd) i++;
        }
        return count;
    }
};

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if(pairs.size()<=1) return pairs.size();
        sort(pairs.begin(),pairs.end(), [](const vector<int> & a, const vector<int>&b){
            if(a[1]==b[1]) return a[0]<b[0]; else return a[1]<b[1];
        });
        int count = 0, end = INT_MIN;
        for(int i = 0; i<pairs.size();i++){
            if(pairs[i][0]>end){
                count++;
                end = pairs[i][1];
            }
        }
        return count;
    }
};

/*
根据start 来sort
*/

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end());
        long end = numeric_limits<long>::min() ; int count = 0;
        for(auto p: pairs)
            if(p[0]>end)
                end = p[1], count++;
            else end = min(static_cast<long>(p[1]), end);
        return count;
    }
};


/*

      
#1) sort by end:  after sorting we know: s1<e1<e2   and s2<e2
#(in order to make it be easier, we do not consider about "="). 
#Then s2 has three possible positions. I am giving those three possibilities by "@". :     @s1@e1@e2 
#Then we have 3 cases.
       #case 1: s2<s1<e1  @<e2 (replace the first "@"by s2 and remove the rest "@")   
                         #s1****e1
         #s2*****************************e2


        #case 2:s1<s2<e1 <e2 
         #s1*****************e1
                      #s2*******************e2
        

       #case 3:s1<e1< s2 <e2 
        #s1************e1
                                     #s2**************e2
       
#2) sort by start(similar as sort by end):   s1@s2@e2@
        #case1:    s1 <e1 <s2< e2
         #s1******e1
                                     #s2************e2


        #case2:    s1<s2<e1<e2
         #s1***************e1
                     #s2**********************e2


        #case3:s1<s2<e2<e1
          #s1************************************e1
                          #s2********e2


*/
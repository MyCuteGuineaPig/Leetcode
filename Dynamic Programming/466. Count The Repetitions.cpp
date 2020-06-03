
/*

Count[k]: 记录当k个s1结束后, 有几个s2可以form
nextIndex[j] = k, 表示当k个s1 结束后，下一个s1开始要找相应的s2[j]


Example:

Input:
s1="abacb", n1=6
s2="bcaa", n2=1

Return:
3
                    
                    0 1    2 3 0      1    2 3 0      1    2 3 0  
S1 --------------> abacb | abacb | abacb | abacb | abacb | abacb 
S2                  b c    a a b      c    a  ab      c    a a 0
Cnt  ----->       |      |   1   |       |    2  |       |   3
 
在s1结尾更新下面两个
Count           ->     0 |      1|      1|      2|       2|      3
nextIndex ------->     2 |      1|      2|      1|       2|      1
                                        ^
                                        |
                                    find pattern:  2 1 
 start = 0
 prefix = Count[0] = 0
 pattern = (n1 - start) / (k-start) *(cnt - prefix) // prefix 到 pattern 开始是 k - start
         = (6 - 1) / (3 - 1) * (1 - 0)
         = 2 
suffix = count[start + (n1 - start) % (k - start) ]  // (n1 - start) % (k - start) < k-start
       = count[ 0 + (6-1) % (3-1)]
       = count[1]
       = 1                        



*/


class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        if(s1.size()*n1 < s2.size() * n2)
            return 0;
        unordered_map<int,int>count;
        unordered_map<int,int>nextIndex; 
        //key is index for s2 to begin search in s1, value is k (how many s1)
        int cnt = 0, j = 0;
        for(int k = 1; k<=n1; ++k){
            for(int i = 0; i<s1.size(); ++i){
                if(s1[i] == s2[j]){
                    if(++j == s2.size()){
                        cnt++;
                        j = 0;
                    }
                }
            }
            
            if(nextIndex.count(j)){
                int start = nextIndex[j];
                int prefix = count[start];
                int pattern = (n1 - start) / (k-start) *(cnt - prefix);
                int suffix = count[start + (n1 - start) % (k-start)] - prefix;
                return (prefix + pattern + suffix) / n2;
            }
            
            count[k] = cnt;
            nextIndex[j] = k;
        }
        return count[n1]/n2;
    }
};


class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1Len = s1.size(), s2Len = s2.size(), index1 = 0, index2 = 0;
        unordered_map<int,pair<int,int>>nextIndex;
        while(index1<n1*s1Len){
            int i = index1 % s1Len, j = index2 % s2Len;
            if(s1[i] == s2[j]){
                if(j== 0){
                    j = (index2+1)% s2Len;
                    if(nextIndex.count(i)==0){
                        nextIndex[i] = {index1, index2};
                    }
                    else{
                        int l1 = index1-nextIndex[i].first, l2 = index2 - nextIndex[i].second;
                        index2 += (n1*s1Len - index1)/l1*l2; //跳过match 的 pattern
                        index1 += (n1*s1Len - index1)/l1*l1;//跳过match 的 pattern
                    }
                }
                if (index1 < s1Len * n1) index2++; //不可以去掉 if (index1 < s1Len * n1)， 比如  "aa" 2 "a" 1, 去掉返回5, 正确是4
                                                        //index2 = 1, index1 = 2, l1 = 2, l2 = 2 ,  (n1*s1Len - index1)/l1*l2 = (4-2)/2*2 = 2, 在index1 到 n1*s1Len, 可以跳两个位置 
                                                        //因为跳过之后 index1 = s1Len*n1, ++index, 会多算实际的index2  
            }
            index1++;
        }
        return index2/n2/s2Len;
    }
};




class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1Len = s1.size(), s2Len = s2.size(), index1 = 0, index2 = 0;
        unordered_map<int,pair<int,int>>nextIndex;
        while(index1<n1*s1Len){
            int i = index1 % s1Len, j = index2 % s2Len;
            if(s1[i] == s2[j]){
                if(j==s2Len-1){
                    if(nextIndex.count(i)==0){
                        nextIndex[i] = {index1, index2};
                    }
                    else{
                        int l1 = index1-nextIndex[i].first, l2 = index2 - nextIndex[i].second;
                        index2 += (n1*s1Len-1 - index1)/l1*l2;  //跳过match 的 pattern
                        index1 += (n1*s1Len-1 - index1)/l1*l1;  //跳过match 的 pattern
                    }
                }
                index2++;
            }
            index1++;
        }
        return index2/n2/s2Len;
    }
};


//aslo work but slow, 找循环
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int len=s2.size();
        vector<int> dp(len);
        for(int i=0;i<len;i++){
            int start=i;
            for(char ch : s1)if(ch==s2[start%len])start++;
            if(start==i)return 0;
            dp[i]=start-i;
        }
        int idx=0;
        for(int i=0;i<n1;i++)idx+=dp[idx%len]; //找下一个点
        return idx/len/n2;
    }
};


/*
"bacaba"
3
"abacab"
1
      b  a  c  a   b  a | b  a  c  a   b  a | b  a  c  a  b  a |
         a         b  a |       c  a   b  a | b  a  c  a  b  a |
j   0                 3 |                 1 |                1 | 
l1  0                 5 |                11 |                17|   
l2  0                 2 |                 6 |                12|   

map = {{3,{3,5}} {3,{5,2}}, {1,{11,6}} };
     index1 17 index2 12
      nextIndex[j].first 11 nextIndex[j].second 6
      l1 = index1-dp[j].first =  6  //l1 重复的长度
      l2 = index2 - dp[j].second = 6 //l2 重复的长度
     (n1*s1Len - index1)
    (n1*s1Len - index1) 1 while 0
new index1 17 index2 12



"acb"
4
"ab"
2
        a   c   b |  a   c   b |  a   c   b |  a   c   b |
        a       b |  a       b |

以s2 length 为base的
map = { {2,{2,1}},  }}
len1 = index1 - dp[i1].first  = 5 - 2 = 3 
len2 = index2 - dp[i1].second = 3 - 1 = 2
change2 = (n1*s1Len-1 - index1)/l1*l2 = (4*3-1 - 5)/3*2 = 7/3*2 = 4;
changed1 = (n1*s1Len-1 - index1)/l1*l1 = (4*3-1 - 5)/3*3 = 6;
index1 += (n1*s1Len - index1)/l1*l1 = 5 + 6 = 11
index2 += (n1*s1Len - index1)/l1*l2 = 3 + 4 = 7;
index1++, index2++ 

return 8/2/2 = 1;

以s2 index 0 为base
map = { {0,{0,0}},  }}
len1 = index1 - dp[i1].first  = 3 - 0 = 3 
len2 = index2 - dp[i1].second = 2 - 0 = 2
change2 = (n1*s1Len - index1)/l1*l2 = (4*3 - 3)/3*2 = 6;
changed1 = (n1*s1Len - index1)/l1*l1 = (4*3 - 3)/3*3 = 9;
index1 += (n1*s1Len - index1)/l1*l1 = 3 + 9 = 12
index2 += (n1*s1Len - index1)/l1*l2 = 2 + 6 = 8; 

return 8/2/2 = 2;

*/


/*
798. Smallest Rotation with Highest Score


Given an array A, we may rotate it by a non-negative integer K so that the array becomes A[K], A[K+1], A{K+2], ... A[A.length - 1], A[0], A[1], ..., A[K-1].  
Afterward, any entries that are less than or equal to their index are worth 1 point. 

For example, if we have [2, 4, 1, 3, 0], and we rotate by K = 2, it becomes [1, 3, 0, 2, 4].  
This is worth 3 points because 1 > 0 [no points], 3 > 1 [no points], 0 <= 2 [one point], 2 <= 3 [one point], 4 <= 4 [one point].

Over all possible rotations, return the rotation index K that corresponds to the highest score we could receive.  
If there are multiple answers, return the smallest such index K.

Example 1:
Input: [2, 3, 1, 4, 0]
Output: 3
Explanation:  
Scores for each K are listed below: 
K = 0,  A = [2,3,1,4,0],    score 2
K = 1,  A = [3,1,4,0,2],    score 3
K = 2,  A = [1,4,0,2,3],    score 3
K = 3,  A = [4,0,2,3,1],    score 4
K = 4,  A = [0,2,3,1,4],    score 3
So we should choose K = 3, which has the highest score.

 

Example 2:
Input: [1, 3, 0, 2, 4]
Output: 0
Explanation:  A will always have 3 points no matter how it shifts.
So we will choose the smallest K, which is 0.
Note:

A will have length at most 20000.
A[i] will be in the range [0, A.length].


*/

/*

change: 记录当从 K-1 到第k步时候的变化. 是根据change[0]来变化的, 假如change[0] = -1, change[1] = 0，表示向左移动1步，让总共的和加1
用N 表示当前数的长度，
假设现在数 0 < A[i] < A.length;  数从k-1步到k步移动 可以分三种情况讨论
1. 不额外得分也不失分， 当A[i] > i, 向左移动最多让 A[i] == i, 还是得分
2. 得一分，从数从0 到N-1;  因为第0位的数大于0 （假设A[i]都大于0）
3. 失去一分， 当A[i] == i, A[i]从i移动到i-1 

第1种情况不用管， 第二种情况在change[i] 开始前给change[i] + 1;
第三种情况 需要 算 turning point k; 对于开始位置在i的A[i],  k = ( i - A[i] + 1 + N)%N
比如 i = 1, A[1] = 4, N = 6, 我们需要把4放在3的位置，4 - > 3 让change - 1； （4放在4的位置是最后一次算分）
i - A[i] 是现在index到A[i]的所需的要步数， + 1, 表示到 A[i] - 1的位置;

然后我们acculumate change: 
change[i] += change[i-1] + 1 (0 到 A.length - 1)

再来讨论A[i] = 0 or A[i] = A.length();  实际上不管A[i] = 0还是A[i] =A.length(), 他们都是fake point
因为A[i] = 0 永远都会算一分， A[i] = A.length 永远都不会算分 (因为最大index是A.length()-1)
k = ( i - 0 or N + 1 + N) % N = i + 1;  change[i+1] --; 0， N当移动 i + 1步时减去1
N 在第i 位， N从 i位移动到0位需要 i步， 第i+1步是把N 从0移动到A.length()-1; 但是无论谁移动，都会+1（从0到A.length()-1）;
    所以N的change[i+1]--是为了抵消到那个1. 因为N无论在哪都不算分
0 在第i位，0从 i位移动到0位需要 i步， 第i+1步是把0 从0移动到A.length()-1; 但是无论谁移动，都会+1（从0到A.length()-1）;
    所以0的change[i+1]--是为了抵消到那个1， 因为0在哪都算分

*/

class Solution {
public:
    int bestRotation(vector<int>& A) {
        const int N = A.size();
        int change[N] = {0};
        for(int i = 0; i<N; i++)
            change[(i - A[i] + 1 + N)%N]--;
        for(int i = 1; i<N; i++)
            change[i] += change[i-1] + 1;
        return distance(change, max_element(change, change+N));
    }
};


class Solution {
    public int bestRotation(int[] A) {
        int len = A.length;
        int[] counter = new int[len];
        for (int i = 0; i < len; i++) {
            counter[(i + 1) % len]++;
            counter[(i - (A[i] - 1) + len) % len]--;
            if (i >= A[i]) counter[0]++;
        }
        
        int max = counter[0], bestK = 0;
        for (int i = 1; i < counter.length; i++) {
            counter[i] += counter[i - 1];
            if (counter[i] > max) {
                max = counter[i];
                bestK = i;
            }
        }
        
        return bestK;
    }
}



class Solution {
public:
    int bestRotation(vector<int>& A) {
        int N = A.size();
        int counter[N] = {0};
        for (int i = 0; i < N; i++) {
            counter[(i + 1) % N]++;
            counter[(i - (A[i] - 1) + N) % N]--;
            if (i >= A[i]) counter[0]++; //算0的sum
        }
        
        int max = counter[0], bestK = 0;
        for (int i = 1; i < N; i++) {
            counter[i] += counter[i - 1];
            if (counter[i] > max) {
                max = counter[i];
                bestK = i;
            }
        }
        
        return bestK;
    }
};
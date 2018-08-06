/*
605. Can Place Flowers


Suppose you have a long flowerbed in which some of the plots are planted and some are not. 
However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.

Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), 
and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: True
Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: False
Note:
The input array won't violate no-adjacent-flowers rule.
The input array size is in the range of [1, 20000].
n is a non-negative integer which won't exceed the input array size.


*/


class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int cnt = 0;
        for(int i = 0; i<flowerbed.size(); i++){
            if(flowerbed[i] == 0 && (i == 0 || flowerbed[i-1] == 0) && (i==flowerbed.size()-1 || flowerbed[i+1] == 0))
            {
                cnt++;
                flowerbed[i] = 1;
            }
            if(cnt >= n) return true;
        }
        return false;
    }
};

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        flowerbed.insert(flowerbed.begin(),0);
        flowerbed.push_back(0);
        for(int i = 1; i < flowerbed.size()-1; ++i)
        {
            if(flowerbed[i-1] + flowerbed[i] + flowerbed[i+1] == 0)
            {
                --n;
                ++i;
            }
                
        }
        return n <=0;
    }
};

/*

DP will always work for any problem that can be solved by greedy 
which deals with making local choices while DP considers all global choices. 
There are many problems where greedy isn't sufficient to get an optimal solution.

However, this problem isn't one. Here each local choice is enough to get the optimal solution. 
You can prove it by induction. No matter what other choices you consider,
 for any given row of plants, you will find that the greedy solution will always yield the optimal solution. 
 The other choices that you traverse here would simply be a waste.

*/


/*

算1之间0的个数， 比如开始是 // 0 0 0 0 0 0 1
                           1   1   1     = count = (7-1)/2 = 3

                比如开始是 // 0 0 0 0 0 1
                             1   1  1    = count = (6-1)/2 = 2 最后一个1无效

结尾如果是0， 结尾后一位也算上是0，就好比count 开始设为1， 所以结尾时count不减去， 直接除以2


1.首尾为0的时候，在首位把count设为1.因为[001***]这种算1个
2末位为0的时候，else不会执行，这样count就是末位0的个数，直接进行计算
3.中间为0的时候，用(count-1)/2
*/
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 1;
        int result = 0;
        for(int i=0; i<flowerbed.size(); i++) {
            if(flowerbed[i] == 0) {
                count++;
            }else {
                result += (count-1)/2;
                count = 0;
            }
        }
        if(count != 0) result += count/2;
        return result>=n;
    }
};


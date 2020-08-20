

/*
🔍
如果现在rating 比两边都邻居大， 拿的糖需要比两面邻居都要多, candy[i] = max(candy[i-1], candy[i+1])+1,
如果只比左面大，candy[i] = candy[i-1] + 1
如果只比右面大，candy[i] = candy[i+1] + 1

step1: 看左面邻居
先从左到右loop 一遍，如果现在比左面的大，糖就比左面+1， 小于的或者等于的不管，给他们先assign 糖为1

step2: 看右面邻居
从右往左loop，如果比右面大，对比右面糖+1， 和现在比(现在是算了左面的)谁大，keep大的

比如 [1,2,3,1], 在3的位置 左面糖是2，右面糖是1，keep 大的为1
比如 [1,5,6,4,3,2,1], 在6的位置，右侧糖更多

不能担心极值在两边， 比如[10,9,8,6]
从左面loop, candy = [1,1,1,1]
但是从右面loop完，candy 会修正的 = [4,3,2,1]

也不用担心小的值在中间
比如[9,8,7,1,4,5], 中间1最小，
从左面loop, candy = [1,1,1,1, 2, 3] 把小的值(1)右面改了
从右面loop完，candy = [4,3,2,1，2，3] 把小的值(1)左面改了


*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size()<=1) return ratings.size();
        int n = ratings.size();
        vector<int>candy(n, 1);

        for(int i = 1; i<n; i++)
            if(ratings[i] > ratings[i-1])
                candy[i] = candy[i-1]+1;
        
        for(int i = n-2; i>=0; i--)
            if(ratings[i] > ratings[i+1])
                candy[i] = max(candy[i], candy[i+1]+1);
        
        return accumulate(candy.begin(), candy.end(), 0);
    }
};



class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> left(n), right(n);
        left[0] = right[n - 1] = 1;
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
            else left[i] = 1;
            if (ratings[n - i] < ratings[n - i - 1]) right[n - i - 1] = right[n - i] + 1;
            else right[n - i - 1] = 1;
        }
        int c = 0;
        for (int i = 0; i < n; ++i) c += max(left[i], right[i]);
        return c;
    }
};



class Solution {
public:
    int candy(vector<int>& ratings) {
        typedef pair<int, int> pin;
        priority_queue<pin, vector<pin>, greater<pin>> pq; //由小到大一个一个pop,然后变邻居的糖
        for(int i = 0; i < ratings.size(); i++)
            pq.push({ratings[i], i});
        vector<int> candies(ratings.size(), 1);
        while(pq.size()){
            pin next = pq.top();
            pq.pop();
            int val = next.first, idx = next.second;
            if(idx - 1 >= 0 && ratings[idx-1] > ratings[idx] && candies[idx-1] <= candies[idx])
                candies[idx-1] = candies[idx] + 1;
            if(idx + 1 < ratings.size() && ratings[idx+1] > ratings[idx] && candies[idx+1] <= candies[idx])
                candies[idx+1] = candies[idx] + 1;
        }
        int su = 0;
        for(auto c:candies)
            su += c;
        return su;
    }
};



/*

Complexity O(n)
Space: O(1)

http://www.allenlipeng47.com/blog/index.php/2016/07/21/candy/

当现在数减小时候 countdown ++， 
当现在数比前一个数大于等于，先把之前减小的部分算上，把连续countdown 的最后一个高度(连续最右侧的)假设为1，连续下降的起点也是最左侧高度为(countdown)
那么这些countdown的高度是 (1+countdown)*countdown/2

如果下降最左侧 等于或者高于 上一个高度，需要增高上一个高度，增高到 countdown + 1, 因为之前算过了pre, 
那么pre 到 countdown + 1增加的是 countdown - pre + 1



*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size()<=1) return ratings.size();
        int total = 1, pre = 1, countdown = 0;
        for(int i = 1; i<ratings.size(); i++){
            if(ratings[i] >= ratings[i-1]){
                if(countdown > 0){
                    total += (1+countdown)*countdown/2;
                    if(countdown>=pre){
                        total += countdown - pre + 1;
                    }
                    pre = 1;
                    countdown = 0;
                }
                pre = ratings[i] == ratings[i-1] ? 1 : pre+1;
                total += pre;
                
            }else{
                countdown++;
            }
        }
        if(countdown > 0){
            total += (1+countdown)*countdown/2;
            if(countdown>=pre)
                total += countdown - pre + 1;
        }
        return total;
    }
};



//2020 下面的decreaseLen =  countdown + 1;
class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.empty())
            return 0;
        int res = 1, last = 1;
        for(int i = 1; i < ratings.size(); ++i){
            if(ratings[i] < ratings[i-1])
            {
                int j = i;
                while(j < ratings.size() && ratings[j] < ratings[j-1])
                    ++j;
                int decreaseLen = j - i + 1;
                res += (decreaseLen)*(decreaseLen-1)/2 + max(0, decreaseLen - last);
                //比如 1 2 3 4 5 3 2 1,   5的糖是5, 后面的需要的糖是 3 + 2 + 1, 所以不用补5的糖
                //比如 1 2 5 3 2 1,       5的时候糖是3, 3的糖也是3， 需要补一个糖, decreaseLen - last = 4 -3 = 1
                last = 1;
                i = j - 1;
            }else if(ratings[i] > ratings[i-1]){
                res += last + 1;
                ++last;
            }else{
                res += 1;
                last = 1;
            }
        }
        return res;
    }
};


/**
 add some explain about peak >= down ? -1:0



when peak >= down, the candy for the peak still don't need to change.

For example, [0, 1, 20, 9, 8, 7], for the first 5 number, we need to assign [1,2,3,2,1] candies.
But when 7 comes up, we need to raise the value of the peak, which is 3 above, it need to be 4, 
    [1,2,4,3,2,1]
This solution here, make it to be [1,2,3,1,2,4], the sum are same. Really brilliant.
 */
class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.size() == 0) return 0;
        int ret = 1;
        int up = 0, down = 0, peak = 0;
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i - 1] < ratings[i]) {
                peak = ++up;
                down = 0;
                ret += 1 + up;
            } else if (ratings[i - 1] == ratings[i])  {
                peak = up = down = 0;
                ret += 1;
            } else {
                up = 0;
                down++;
                ret += 1 + down + (peak >= down ? -1 : 0);
            }
        }

        return ret;
    }
};




/*

Ratings:
                    Peak
        Peak        |
        |           | |
      | |           | | |   
    | | | |       | | | | |       | | |
  | | | | | |   | | | | | | |     | | |
| | | | | | | | | | | | | | | | | | | |
                Candies:
1 2 3 4 5 3 2 1 2 3 5 4 3 2 1 1 1 2 1 1
x---a---x
        x--b--x    


if ((oldsign > 0 && newsign == 0)  ||
                (oldsign < 0  && newsign >= 0) )


(oldsign > 0 && newsign == 0) 而不是 (oldsign > 0 && newsign <= 0) : 
        比如  [1,4,3,2,2,1], 到3时候, peak = 2, 而真实的peak 应该是4

如果没有这个(oldsign > 0 && newsign == 0) 条件，
   比如 [1,2,87,87,87,2,1] 得到11, 正确答案是13:  会少算了一个max点， 第一个87是第一个peak, 没有算进去, 只是在return 前加了第二个peak(87,2,1)

 */


class Solution {
public:
int slope(int n)
    {
        return (n*(n+1))/2;
    }

    int candy(vector<int> &ratings) {
        if (ratings.size() <= 1 )
        {
            return ratings.size();
        }
        int tot = 0;        // The final amount of candies
        int up = 0;         // Lenght of the last ascending slope
        int down = 0;       // Lenght of the last descending slope
        int oldsign = 0;    // Previous ratings trend (1 = ascending, -1 == descending, 0 = stable) 

        for (int i = 1; i< ratings.size(); i++)
        {
                        // Current ratings trend, same meaning as oldsign
            int newsign = ratings[i] > ratings[i-1] ? 1 : 
                          ratings[i] < ratings[i-1] ? -1 : 0;
                        // We can calculate the contribution of a slope 
                        // when that slope ends and it's not the peak of a mountain,
                        // that's why we have "newsign == 0" and not "newsign <= 0"
            if ((oldsign > 0 && newsign == 0)  ||
                (oldsign < 0  && newsign >= 0) )
                {
                        // The peak of the mountain should have max(up,down)+1
                        // candies, but the end of the mountain is the beginning of
                        // the next sequence, so we don't the candy at the end of 
                        // the mountain
                    tot += slope(up) + slope(down) + std::max(up, down);
                    up = 0;
                    down = 0;
                }

            if(newsign > 0)
                up++;
            if(newsign < 0)
                down++;
                    // Same rating of the previous child?
                    // Take one candy.If you are better then the next child
                    // the descending slope will take that into account, don't worry
            if(newsign == 0)
                tot++;
                
            oldsign = newsign;
        }
        
                    // Final sequence has to be closed
                    // Why +1? Because we don't have a sequence next!
        tot += slope(up) + slope(down) + std::max(up, down) + 1;
        return tot;
    }
};
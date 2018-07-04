/*
137. Single Number II


Given a non-empty array of integers, every element appears three times except for one, 
which appears exactly once. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,3,2]
Output: 3
Example 2:

Input: [0,1,0,1,0,1,99]
Output: 99
*/


/*
数组为[2,2,2,3]，一共有四个元素，进行四次循环。

第一次循环，one=(0000^0010)&1111=0010=2，two=(0000^0010)&1101=0000=0

第二次循环，one=(0010^0010)&1111=0000=0，two=(0000^0010)&1111=0010=2

第三次循环，one=(0000^0010)&1101=0000=0，two=(0010^0010)&1111=0000=0

第四次循环，one=(0000^0011)&1111=0011=3，two=(0000^0011)&1100=0000=0


第一次 nums[i] ^ one 保持nums[i], (nums[i] ^ one)& ~two 因为two是0，所以(nums[i] ^ one)~two还是nums[i]
nums[i] ^ two 保持nums[i], 但是one = nums[i], 所以~one = one的补集 = two的补集， (nums[i] ^ two) & ~one = 0;

第二次 nums[i] ^ one,两次消掉为0, (nums[i] ^ one) & ~two 因为two是0,two的补集全是1，所以(nums[i] ^ one)~two还是 = 0, 
nums[i] ^ two（因为two为0） 保持nums[i], 但是one = 0, 所以~one = one的补集 = nums[i], (nums[i] ^ two) & ~one =  nums[i] & nums[i] = nums[i]

第三次 nums[i] ^ one,为2（one之前为0）, (nums[i] ^ one) & ~two 因为two是nums[i]，所以(nums[i] ^ one)~two = nums[i] & ~nums[i] = 0, 
nums[i] ^ two（因为two为nums[i]) = 0, (nums[i] ^ two) & ~one =  0 & ~one = 0


不知道大家有没有发现，某个值nums[i]第一次出现的时候，one把它记录了下来，这时候two=0；接着第二次出现的时候，one被清空了，记录到了two里面；
接着第三次出现的时候，one和two都被清空了。

如果一个数组中，所有的元素除了一个特殊的只出现一次，其他都出现了三次，那么根据我们刚刚观察到的结论，最后这个特殊元素必定会被记录在one中(出现一次被one记录)。

有些朋友会说，但是不一定数组都是刚好3个2都在一起，3个4都在一起，都能够满足刚刚这样子的做法。



怎么想出这种方法的：
其实discuss区的大神是设计了一种方法，借由这种方法推出了a和b的变换方式…

我们想要达到的效果其实是——

　　　　　　　　　　   two  one

初始状态　　　　  ：   0   0

第一次碰见某个数x：   0   x（把x记录在one中）

第二次碰见某个数x：   x   0（把x记录在two中）

第三次碰见某个数x：   0   0（把one和two都清空，可以处理其他数）

还记得我们之前处理“所有元素都出现两次，只有一个特殊元素出现一次”的问题吗？其实我们那会想要达到的状态也是——

　　　　　　　　　　  one

初始状态　　　　  ：   0

第一次碰见某个数x：   x(把x记录在one中）

第二次碰见某个数x：   0(把one清空）

然后我们刚好就找到了异或运算可以处理这个问题。

那么这次我们同样利用异或运算，看能不能设计出一种变换的方法让one和two按照上述变换规则，进行转换。

one=0时碰到x，就变成x；one=x时再碰到x，就变成0，这个不就是异或吗？所以我们也许可以设计one= one xor x。

但是当one=0时再再碰到x，这时候one还是要为0，但这时候不同的是two=x，而前两种情况都是a=0。所以我们可以设计成：one=(one xor x)&~two

同样道理，我们可以设计出：two=(two xor x)&~one

在这种变换规则下，one和two都能按照我们设定的状态来发生转化。最后那个只出现一次的元素必定存储在one中。



Let me describe it to see if I'm understanding it right:

First time number appear -> save it in "ones"

Second time -> clear "ones" but save it in "twos" for later check

Third time -> try to save in "ones" but value saved in "twos" clear it.

*/


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        for(auto i: nums){
            ones = (ones ^ i) & ~twos;
            twos = (twos ^ i) & ~ones;
        }
        return ones;
    }
};


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int length = nums.size();
        
        int res = 0;
        for(int i = 0; i < 32; i++)  // Iterate through every bit
        {
            int count = 0;
            int mask = 1 << i;
            // Find sum of set bits at ith position in all
             // array elements
            for(int j = 0; j < length; j++)
            {
                if(nums[j] & mask)
                    count++;
            }
            // The bits with sum not multiple of 3, are the
             // bits of element with single occurrence.
            if(count % 3)
                res = res | mask;
        }
        
        return res;
    }
};


/*
用mask
https://leetcode.com/problems/single-number-ii/discuss/43295/Detailed-explanation-and-generalization-of-the-bitwise-operation-method-for-single-numbers

statement: 除了一个数出现p此, 其他所有数都出现k次
我们需要log(K)的counter variable 去记录, 如果一个数出现了p次, 我们需要让counter 都变为0，

比如p = 3, k =1,  为了简单，出现的数用1表示，
需要两个counter variable，当1出现第三次，两个counter variable需要变成0
第一次出现 x1 = 1, x2 = 0
第二次出现 x1 = 0, x2 = 1
第三次出现 x1 = 0, x2 = 0, (先是x1 = 1, x2 = 1, 后经过mask 变成都是0)

第二次1出现， 我们需要把x2 = 1, x1 = 0, 如果出现一个1，当前遇到0， 不改变。 所以第二次出现的条件是，当x1 = 1， num[i] = 1
x2 = x2 ^ (x1 & nums[i])
x1 = x1 ^ nums[i]  = 1 ^ 1 = 0;
第三次出现，需要把x1 = x2 = 1



mask的作用是让counter 经过p次都变成0，如果当前不是经过p的倍数，mask = 1111.... , mask & xi = xi, mask不需要工作
需要做and operation to all counters.  xm = xm & mask; x2 = x2& mask; x1 = x1 & mask;
而经历p次后， mask 为0; xi = xi & mask = xi & 0 = 0

mask = ~(y1 & y2 & ... & ym), where yj = xj if kj = 1, and yj = ~xj if kj = 0 (j = 1 to m).
实际上mask是p的binary form的取非, p的binary form代表counter记录的情况。 每个1出现都是独特的。 mask当出现p的倍数时得到0，我们可以取非，
比如当p = 5, x1 = 1, x2 = 0, x3 = 1, 所以让取非前为1,  x1 & ~x2 & x3 = 1
在第一次后， x3 = 0, x2 = 0, x1 = 1; 001
第二次出现  x3 = 0, x2 = 1, x1 = 0;  010
第三次出现 x3 = 0, x2 = 1, x1 = 1;   011
第四次出现 x3 = 1, x2 = 0, x1 = 0;   100
第五次出现 x3 = 1, x2 = 0, x1 = 1;   101  (在mask前)
mask = ~(x1 & ~x2 & x3),  

返回值: 比如p=5, k =3, 返回k的binary form为1位数的counter
k=3， binary form是011, 可以返回x1, 或者x2
*/


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int x1 = 0, x2 = 0, mask = 0;
         
        for (int i : nums) {
            x2 ^= x1 & i;
            x1 ^= i;
            mask = ~(x1 & x2);
            x2 &= mask;
            x1 &= mask;
        }
        return x1;
    }
};

/*

Here is a list of few quick examples to show how the algorithm works:

k = 2, p = 1
k is 2, then m = 1, we need only one 32-bit integer(x1) as the counter. And 2^m = k so we do not even need a mask! A complete java program will look like:
    public int singleNumber(int[] A) {
         int x1 = 0;
         
         for (int i : A) {
             x1 ^= i;
         }
         
         return x1;
    }
k = 3, p = 1
k is 3, then m = 2, we need two 32-bit integers(x2, x1) as the counter. And 2^m > k so we do need a mask. Write k in its binary form: k = '11', then k1 = 1, k2 = 1, so we have mask = ~(x1 & x2). A complete java program will look like:
    public int singleNumber(int[] A) {
         int x1 = 0, x2 = 0, mask = 0;
   
         for (int i : A) {
             x2 ^= x1 & i;
             x1 ^= i;
             mask = ~(x1 & x2);
             x2 &= mask;
             x1 &= mask;
         }

         return x1;  // p = 1, in binary form p = '01', then p1 = 1, so we should return x1; 
                     // if p = 2, in binary form p = '10', then p2 = 1, so we should return x2.
    }
k = 5, p = 3
k is 5, then m = 3, we need three 32-bit integers(x3, x2, x1) as the counter. And 2^m > k so we need a mask. Write k in its binary form: k = '101', then k1 = 1, k2 = 0, k3 = 1, so we have mask = ~(x1 & ~x2 & x3). A complete java program will look like:
    public int singleNumber(int[] A) {
         int x1 = 0, x2 = 0, x3  = 0, mask = 0;
   
         for (int i : A) {
             x3 ^= x2 & x1 & i;
             x2 ^= x1 & i;
             x1 ^= i;
             mask = ~(x1 & ~x2 & x3);
             x3 &= mask;
             x2 &= mask;
             x1 &= mask;
         }
       
         return x1;  // p = 3, in binary form p = '011', then p1 = p2 = 1, so we can
                     // return either x1 or x2. But if p = 4, in binary form p = '100', 
                     // only p3 = 1, which implies we can only return x3.
    }
*/
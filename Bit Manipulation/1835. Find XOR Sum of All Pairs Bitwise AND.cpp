/*
We all know the distributive property that (a1+a2)*(b1+b2) = a1*b1 + a1*b2 + a2*b1 + a2*b2


Explanation
Distributive property is similar for AND and XOR here.
(a1^a2) & (b1^b2) = (a1&b1) ^ (a1&b2) ^ (a2&b1) ^ (a2&b2)
(I wasn't aware of this at first either)



另一种思路,   如果所有arr2 中的数 第一个bit 是奇数个(求所有数第一位bit的xor)，if arr1[0] 第一个bit 为 1, 那么第一个 bit 可以留下来
            如果所有arr2 中的数 第二个bit 是奇数个(求所有数第二位bit的xor)，if arr1[0] 第二个bit 为 1, 那么第二个 bit 可以留下来
              ：  ：  ： ：   ：   ：  ：   ：  ：  ：  ：   ：   ：   ：   ： ：   ：   ：   ：  ：
            如果所有arr2 中的数 第n个bit 是奇数个(求所有数第n位bit的xor)，if arr1[0] 第n个bit 为 1, 那么第二个 bit 可以留下来

        把这n 个 bit 结合到一起(xorb)，就是  (arr1[0] & arr2 [0]) ^ (arr1[0] & arr2[1]) ... (arr1[0] & arr2[n2-1]) 

*/


class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int xora = 0, xorb = 0;
        for (int& a: arr1)
            xora ^= a;
        for (int& b: arr2)
            xorb ^= b;
        return xora & xorb;
    }
};

class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int xorb = 0;
        for (int& b: arr2)
            xorb ^= b;
        
        int ret = 0;
        for (int& a: arr1)
            ret ^= (xorb & a);
        return ret;
    }
};

/*
190. Reverse Bits


Reverse bits of a given 32 bits unsigned integer.

Example:

Input: 43261596
Output: 964176192
Explanation: 43261596 represented in binary as 00000010100101000001111010011100, 
             return 964176192 represented in binary as 00111001011110000010100101000000.
Follow up:
If this function is called many times, how would you optimize it?


*/


class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0; i<32; i++, n = (n>>1)){
            uint32_t t = n & 1;
            res = (res << 1) | t;
        }
        return res;
    }
};


class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t count = sizeof(n) * 8 -1;
        uint32_t r = n;
        
        n = n>> 1;
        while(n)
        {
            r = r<<1;
            r = r | (n&1);
            n = n>>1;
            count--;
        }
        r = r<< count;
        
        return r;
    }
};


/**
1. 16 bits left and right swapped
2. every couple of 8 bits swapped (every other 8 bits are picked by AND operation and 00ff and ff00 as masks equivalent to 0000000011111111 and 1111111100000000)
3. every couple of 4 bits are swapped like above using 0f0f and f0f0 as masks.
4. every couple of 2 bits are swapped using cc and 33 corresponding to 11001100 and 0011011
5. every couple of 1 bit are swapped using aa and 55 corresponding to 10101010 and 01010101
This results in log(D) time complexity in which D is the number of bits.


     /*
	 * 利用高地位交换实现逆序
	 * 两位一组，高低位互换，方法是（取奇数位，偶数位补0，右移1位）| （取偶数为，奇数位补0，左移1位）
	 * 依次四位一组，八位一组，十六位一组，三十二位一组
	 * 由于是无符号位，所以注意得是逻辑右移
	 */
    
 * 
*/
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
};
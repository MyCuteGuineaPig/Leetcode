

/*
找到最左面不符合的index 为leftInvertInd， 把leftInvertInd后面全变为9， 把前一位的数减去1
比如 1231， 不符合是1， 先变成1221, 然后把不符合的变成9 => 1229
*/

class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string s = to_string(N);
        int leftInvertInd = s.size();
        for(int i = s.size()-1; i>0; i--){
            if(s[i-1] > s[i] ){
                leftInvertInd = i;
                s[i-1]--;
            }
        }
        for(int i = leftInvertInd; i<s.size();i++)
            s[i] = '9';
        return stoi(s);
    }
};


class Solution {
    public int monotoneIncreasingDigits(int N) {
        int res = 0;
        int pre = Integer.MAX_VALUE;
        int offset = 1;
        while(N != 0) {
            int digit = N % 10;
            if(digit > pre) {
                res = digit * offset - 1;//比如128400, 到8的时候 8<4; res = 7999
                pre = digit - 1;
            }else {
                res = res + digit * offset;
                pre = digit;
            }
            offset *= 10;
            N = N / 10;
        }
        return res;
    }
    
}

/*
Solution 2: 用N - 减去不符合的数 然后再减去1 也是结果

ind 表示左面最后一位不符合的数，比如 100,  ind = 0,  s.susbtr(ind+1) = 0
因为ind这个数会减去1，所以前面数不能与ind 一样的数

ind !=-1 && s[ind] == s[i] 表示如果碰到一样的，
 比如 188765, 不符合的是ind = 1, 变成 188765 - 88765 - 1= 17999, 如果ind = 2, 变成 188765 - 8765 - 1= 187999, 8>7不对

如果中间有隔数也无所谓，因为隔的数肯定会造成s[i] > s[i+1] ， 比如 187821, ind = 3 = > ind = 1(s[1]>s[2]), 比如189821, ind = 2 (9)
 
*/
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string s = to_string(N);
        int ind = -1;
        for(int i = s.size()-2; i>=0; i--){
            if(s[i] > s[i+1] || ind!=-1 &&s[ind] == s[i] ){ //or ind!=-1 && s[ind] <= s[i] 
                ind = i;
            }
        }
        return ind == -1 ? N : N - stoi(s.substr(ind+1))-1;
    }
};
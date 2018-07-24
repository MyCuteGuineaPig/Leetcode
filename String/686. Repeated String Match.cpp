/*
686. Repeated String Match

Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. 
If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; 
and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.

*/


/*
KMP 算法：利用kmp 先得b的prefix的table

然后两个pointer, 一个pointer i 记录A的位置，一个pointer j记录B的位置，每次对比 A[(i + j)%A.size()] 是否等于B[j] 等于就++j.
直到 j =  b.size() return size： 看 i + j 是不是A的倍数 如果是， 返回 (i + j) / a.size(), 如果不是，还需结果上加一，多的开头或者结尾出来返回 (i + j) / a.size()+1

这样好处是假如到A[i+j]!=B[j]不match, a不用回到这次开始前的下一点(i+1)继续开始，可以直接到 i += j - prefix[j-1]的点


i跳到 i' =  j - prefix[j-1]的原因是： 分两种情况
    -  prefix[j - 1] > 0: 有suffix 也是prefix的情况，这样不动A点, 动B点到上一个prefix的后一点, 继续进行比较，同时调整相对应B的A的起点位置i，
       根据kmp的性质，这样做可以省去重复比较时间
        因为这部分既可以当suffix 也可以当prefix，当suffix（也已经测过A = B） = prefix 的满足起点(B)的需求
     （ 动B的原因: 1. 可能B的前面与现在A(0: i)不match，但是B的前面 可能不代表A的起点，代表A的终点，比如 A : abababc B: ababcabab 
                  2. 始终开始时都要对比此刻A的位置 是不是满足B的起点  b[0] or  b.substr(0,j)） 
        A【i： i' -1 ] 不能做起点的原因：
                  假设 [i: i' - 1]没有 suffix也是prefix的
                  因为每个match 都是要考虑 A的起点i是不是可以作为整个B的起点 A[i:i+j] ?= B[0, j]
                  而前面已经测过 A[i: i+j】 和 B[0: j] match, 那么A[i+1: i+j] 也match B[1: i+j]  
                  但是因为[i,i'- 1] 没有suffix做为prefix，把i+1 设为起点的话，不能满足 B的起点需求 (A[i+1: i+j+1] != B[0: j])
        比如
        A: a a b a a c  (return -1)
        B: a a b a a b a a c

        当j = 5 不match 的时候, p[j = 4] > 0 (aa) 即是prefix 又是suffix，此时不动A (i+j保持不动)，动B到上一个prefix的后一位 j = 2
            i前进到3(A的B相对应的起点)
            A: a a b a a c  (return -1)
               i=0       -
            B: a a b a a b a a c            B的prefix的array是 [0,1,0,1,2,3,4,5,0],
               i=3   a a b a a b a a c

        比如
        A: a b a b a b c  (return 2)
                   _
        B: a b a b c a b a b
               a b a b c a b a b

        当j = 5 不match 的时候, p[j = 4] = 2 > 0 (ab) 即是prefix 又是suffix，此时不动A(i+j保持不动)，动B到上一个prefix的后一位 j = 2, 
            i前进到3(A的B相对应的起点)
            A: a a b a a c  (return 2)
                         -
            B: a a b a a b a a c
                     a a b a a b a a c

            
        因为比较是A[i + j ] 和 B【j] 要保持 i + j 不变，我们已经知道j要回到 j' = prefix [ j- 1], 所以 i + j = i' + j ' = i' + prefix[j-1]
        i' = i + j - prefix[j - 1]
        i' 是下一个B（还是这个prefix的） 起点位置， 

    -  prefix[j - i] = 0, 现在suffix 不能构成prefix，跳过match的部分，因为match的话一定是从j = 0 开始逐一match, 这样没有suffix 不做prefix的，
        我们知道j下个位置会回到0，i就可以到 i + j 的位置继续loop, 
        比如
        A: a b c d f  (return -1)
        B: a b c d z     

        下一次比较
        A: a b c d f (return -1)
                B: a b c d a b   



*/


class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        vector<int>prefix(B.size());
        
        //generate B prefix table KMP
        for(int i = 1, j = 0; i<B.size(); i++){
            while(j > 0 && B[i]!=B[j]) j = prefix[j-1];
            if(B[i] == B[j]) ++j;
            prefix[i] = j;
        }
        
        for(int i = 0, j = 0; i<A.size(); i += j - prefix[j-1], j = prefix[j-1]){
            while(j<B.size() && A[(i+j) % A.size()] == B[j]) j ++;
            if(j == B.size()) return (i+j)/(A.size()) + ((i+j) % A.size() ? 1 : 0);
            if(j == 0) j = 1; // avoid overflow like prefix [ 0 - 1]
        }
        return -1;
    }
};

/*


rolling Hash:

每次开始减去原来的hash，加上现在的hash。当两个hash一样时，再对比是不是真的一样

indetail:
每次需要用原来的hash减去最开始的数 再除以质数，加上现在的数*power 

x = old hash - val (char)
x = x/prme
new hahs = x + prime^(m-1) * x

举例 质数为3  a->1, b -> 2, c -> 3, d -> 4, e -> 5 

a b e d a

a b e 的hash =  1 + 2*3^1 + 5 * 3^2 = 1 + 6 + 45 = 52

b e d 的hash =  (oldhash - 1（a的对应值) )/3 + 4（d的对应值)* 3 ^ 2 = (52 - 1)/3 + 4 * 9 = 17 + 36 = 53

e d a 的hash = (oldhash - 2（e的对应值) )/3 + 1（a的对应值)* 3 ^ 2 = (53 - 2)/3 + 1 * 9 = 17 + 9 = 26


*/




// Rabin-Karp Algorithm (rolling hash)
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        static const uint64_t M = 1000000007;
        static const uint64_t p = 113; 
        static const uint64_t p_inv = pow(p, M - 2, M);

        const auto q = (B.length() + A.length() - 1) / A.length();
    
        uint64_t b_hash = 0, power = 1;
        for (int i = 0; i < B.length(); ++i) {
            b_hash += power * B[i];
            b_hash %= M;
            power = (power * p) % M;
        }

        uint64_t a_hash = 0; power = 1;
        for (int i = 0; i < B.length(); ++i) {
            a_hash += power * A[i % A.length()];
            a_hash %= M;
            power = (power * p) % M;
        }
        if (a_hash == b_hash && check(0, A, B)) {
            return q;
        }
        
        power = (power * p_inv) % M;
        for (int i = B.length(); i < (q + 1) * A.length(); ++i) {
            a_hash -= A[(i - B.length()) % A.length()];
            a_hash *= p_inv;
            a_hash += power * A[i % A.length()];
            a_hash %= M;
            if (a_hash == b_hash && check(i - B.length() + 1, A, B)) {
                return i < q * A.length() ? q : q + 1;
            }
        }
        return -1;
    }

private:
    bool check(int index, const string& A, const string& B) {
        for (int i = 0; i < B.length(); ++i) {
            if (A[(i + index) % A.length()] != B[i]) {
                return false;
            }
        }
        return true;
    }

    uint64_t pow(uint64_t a,uint64_t b, uint64_t m) {
        a %= m;
        uint64_t result = 1;
        while (b) {
            if (b & 1) {
                result = (result * a) % m;
            }
            a = (a * a) % m;
            b >>= 1;
        }
        return result;
    }
};


//brute force
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string as = a;
        for (int rep = 1; rep <= b.length() / a.length() + 2; rep++, as += a)
            if (as.find(b) != string::npos) return rep;
        return -1;
    }
};
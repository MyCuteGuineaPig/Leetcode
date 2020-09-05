//2020 
class Solution {
public:
    string strWithout3a3b(int A, int B) {
        string res = "";
        int cnt = 0;
        while(A>0 || B>0){
            if(A > B && cnt < 2 || cnt == -2){
                res += 'a';
                cnt = cnt >= 0 ? cnt + 1 : 1;
                --A;
            }else{
                res += 'b';
                cnt = cnt <= 0 ? cnt - 1 : -1;
                --B;
            }
        }
        return res;
    }
};


class Solution {
public:
    string strWithout3a3b(int A, int B) {
        if(A == 0) return string(B, 'b');
        else if(B == 0) return string(A, 'a');
        else if(A == B) return "ab" + strWithout3a3b(A - 1, B - 1);
        else if(A > B) return "aab" + strWithout3a3b(A - 2, B - 1);
        else return strWithout3a3b(A - 1, B - 2) + "abb";
    }
};


class Solution {
public:
    string strWithout3a3b(int A, int B) {
        if(A == 0) return string(B, 'b');
        else if(B == 0) return string(A, 'a');
        else if(A == B) return "ab" + strWithout3a3b(A - 1, B - 1);
        else if(A > B) return "aab" + strWithout3a3b(A - 2, B - 1);
        else return  "bba" + strWithout3a3b(A - 1, B - 2) ;
    }
};

/*
1. If the initial number of As is greater than Bs, we swap A and B.
2. For each turn, we add 'a' to our string.
3. If the number of remaining As is greater than Bs, we add one more 'a'.
4. Finally, we add 'b'.


 */
class Solution {
public:
    string strWithout3a3b(int A, int B, char a = 'a', char b = 'b', string res = "") {
      if (B > A) return strWithout3a3b(B, A, b, a);
      while (A-- > 0) {
        res += a;
        if (A > B) res += a, A--;
        if (B-- > 0) res += b;
      }
      return res;
    }
};


class Solution {
public:
    string strWithout3a3b(int A, int B, char a = 'a', char b = 'b') {
      if (B > A) return strWithout3a3b(B, A, b, a);
      if (B == 0) return string(A, a);
      return string(A > B ? 2 : 1, a) + b + strWithout3a3b(A - (A > B ? 2 : 1), B - 1, a, b);
    }
};


//straigt-forward
class Solution {
public:
    string strWithout3a3b(int A, int B) {
        string sb = "";
        while(A + B > 0) {
            int l = sb.size();
            if (l > 1 && sb[l - 2] == sb[l - 1]) {
                if (sb[l - 1] == 'a') {
                    sb += 'b';
                    B--;
                } else {
                    sb += 'a';
                    A--;
                }
            } else {
                if (A > B) {
                    sb += 'a';
                    A--;
                } else {
                    sb += 'b';
                    B--;
                }
            }
        }
        return sb;
    }
};


class Solution {
public:
    string strWithout3a3b(int A, int B) {
        std::string res;
        
        while (A && B) {
            if (A > B) {
                res += "aab";
                A--;
            } else if (B > A) {
                res += "bba";
                B--;
            } else {
                res += "ab";
            }
            A--;
            B--;
        }
        while (A--) res += "a";
        while (B--) res += "b";
        return res;
    }
};
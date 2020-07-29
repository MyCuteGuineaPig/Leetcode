/*
'R......R' => 'RRRRRRRR'
'R......L' => 'RRRRLLLL' or 'RRRR.LLLL'
'L......R' => 'L......R'
'L......L' => 'LLLLLLLL'
*/

class Solution {
public:
    string pushDominoes(string d) {
        d = 'L' + d + 'R'; //'L' 往左倒， R 往右倒，不会影响结果
        string res = "";
        for (int i = 0, j = 1; j < d.length(); ++j) {
            if (d[j] == '.') continue;
            int middle = j - i - 1;
            if (i > 0) res += d[i];
            if (d[i] == d[j]) res += string(middle, d[i]);
            else if (d[i] == 'L' && d[j] == 'R') res += string(middle, '.');
            else res += string(middle / 2, 'R') + string(middle % 2,'.') + string(middle / 2, 'L');
            i = j;
        }
        return res;
    }
};
/*
Keep track of last seen 'L' and 'R' as indices (variables l and r).

1. If you see 'R' and R > L, you have R....R, turn everything to 'R'.
2. If you see 'R' and R < L, you have L...R and you don't need to do anything.
3. If you see 'L' and L > R, you have L....L, turn everything to 'L'.
4. if you see 'L' and L < R, you have R....L, have to pointers from both sides, 
    lo and hi, turn a[lo]='R' and a[hi] = 'L', increment lo, decrement hi, make sure you do nothing when lo=hi
5. Watch out for edge cases. Note i<=dominoes.length(), this is to deal with L.. Also note L and R are initialized to -1, not 0.


 */

class Solution {
public:
    string pushDominoes(string d) {
        string s = d;
        int n = d.size(), l = -1, r = -1;
        for(int i= 0; i <= n; ++i) {
            if(i == n || s[i] == 'R') {
                if (r > l) 
                    while (r < i) s[r++] = 'R'; //R....R
                r = i;
            }
            else if (s[i] == 'L'){  
                if (l > r || (l == -1 && r == -1))//L..L, turn all to L
                    while (++l < i)
                        a[l] = 'L'; // R.. L ... L 
                                    // r   l     i
                else {//R...L
                    l = i;
                    int lo = r + 1, hi = l - 1;
                    while (lo < hi) { //one in the middle stays '.'
                        a[lo++] = 'R';
                        a[hi--] = 'L';
                }
                l = r = i;
            }
        }
        return s;
    }
};


/**
left_r_dis[i] is the smallest distance between dominoes[i] and its left R.
right_l_dis[i] is the smallest distance between dominoes[i] and its right L.
 */

class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        vector<int> left_r_dis(n + 1, 0);
        vector<int> right_l_dis(n + 1, 0);
        int r_pos = n + 1;
        for (int i = 0; i < n; ++i) {
            if (dominoes[i] == 'R') {
                r_pos = i;
            }
            else if (dominoes[i] == 'L') {
                r_pos = n + 1;
            }
            left_r_dis[i] = r_pos == n + 1 ? n + 1 : i - r_pos;
        }
        int l_pos = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (dominoes[i] == 'L') {
                l_pos = i;
            }
            else if (dominoes[i] == 'R') {
                l_pos = -1;
            }
            right_l_dis[i] = l_pos == -1 ? n + 1 : l_pos - i;
        }
        
        string result = dominoes;
        for (int i = 0; i < n; ++i) {
            if (left_r_dis[i] < right_l_dis[i]) result[i] = 'R';
            else if (left_r_dis[i] > right_l_dis[i]) result[i] = 'L';
            //else
        }

        return result;
    } 
};


/**
 Simulation
 */
class Solution {
public:
    string pushDominoes(string ds) {
      for (string s = ds; ; s = ds) {
        for (auto i = 0, d = s[i] == 'L' ? -1 : 1; i < s.size(); d = s[++i] == 'L' ? -1 : 1)
          if (s[i] != '.' && i + d >= 0 && i + d < s.size() && s[i + d] == '.' &&
            (i + d * 2 < 0 || i + d * 2 >= s.size() || s[i + d * 2] != (s[i] == 'L' ? 'R' : 'L'))) ds[i + d] = s[i];
        if (s == ds) return s;
      }
    }
};
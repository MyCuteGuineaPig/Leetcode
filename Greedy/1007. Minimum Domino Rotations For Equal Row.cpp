class Solution {
  public:
  /*
  Return min number of rotations 
  if one could make all elements in A or B equal to x.
  Else return -1.
  */
  int check(int x, vector<int>& A, vector<int>& B, int n) {
    // how many rotations should be done
    // to have all elements in A equal to x
    // and to have all elements in B equal to x
    int rotations_a = 0, rotations_b = 0;
    for (int i = 0; i < n; i++) {
      // rotations coudn't be done
      if (A[i] != x && B[i] != x) return -1;
      // A[i] != x and B[i] == x
      else if (A[i] != x) rotations_a++;
      // A[i] == x and B[i] != x    
      else if (B[i] != x) rotations_b++;
    }
    // min number of rotations to have all
    // elements equal to x in A or B
    return min(rotations_a, rotations_b);
  }

  int minDominoRotations(vector<int>& A, vector<int>& B) {
    int n = A.size();
    int rotations = check(A[0], A, B, n);
    // If one could make all elements in A or B equal to A[0]
    if (rotations != -1 || A[0] == B[0]) return rotations;
    // If one could make all elements in A or B equal to B[0]
    else return check(B[0], A, B, n);
  }
};


class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        vector<int>cnt(7); //total number need to add to A.size()
        vector<int>flipA(7);
        vector<int>flipB(7);
        for(int i =0; i<A.size(); ++i){
            ++cnt[A[i]];  
            if(A[i]!=B[i]){
                ++cnt[B[i]];
                ++flipA[B[i]];
                ++flipB[A[i]];   
            }
        }
        
        int res = A.size()+1;
        for(int i = 1; i<7;++i){
            if(cnt[i] == A.size())
                res = min(res, min(flipA[i], flipB[i]));
        }
        
        return res > A.size() ? -1: res;
    }
};




class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        vector<int> countA(7), countB(7), same(7);
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            countA[A[i]]++;
            countB[B[i]]++;
            if (A[i] == B[i])
                same[A[i]]++;
        }
        for (int i  = 1; i < 7; ++i)
            if (countA[i] + countB[i] - same[i] == n)
                return n - max(countA[i], countB[i]);
        return -1;
    }
};

class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
          auto top = A[0], bot = B[0], top1 = 0, bot1 = 0, top2 = 0, bot2 = 0;
          for (auto i = 0; i < A.size(); ++i) {
            if (A[i] != top && B[i] != top) top = 0;
            if (A[i] != bot && B[i] != bot) bot = 0;
            top1 += A[i] == top;
            bot1 += B[i] == top;
            top2 += A[i] == bot;
            bot2 += B[i] == bot;
          }
          return top || bot ? min(A.size() - max(top1, bot1), A.size() - max(top2, bot2)) : -1;
    }
};
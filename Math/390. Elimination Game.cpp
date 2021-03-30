class Solution {
public:
    int lastRemaining(int n) {
        int left = true;
        int head = 1, step = 1;
        while(n > 1){
            if(left || n % 2 ==1)
                head = head + step;
            step *= 2;
            n /= 2;
            left = !left;
            
        }
        return head;
    }
};


class Solution {
public:
    int lastRemaining(int n) {
    return leftToRight(n);
    }
    
    
    int leftToRight(int n) {
      if(n <= 2) return n;
    // scan from left to right is simple, the length of array doesn't matter
    // [1, 2, 3, 4] -> 2 * [1, 2]
    // [1, 2, 3, 4, 5] -> 2 * [1, 2]
      return 2 * rightToLeft(n / 2);
    }

    int rightToLeft(int n) {
      if(n <= 2) return 1;
     // else if the length of array is odd, we will get only even number
     // [1, 2, 3, 4, 5] -> [2, 4] = 2 * [1, 2]

      if(n % 2 == 1) return 2 * leftToRight(n / 2);
       // if the length of array is even, we will get only odd number
       // [1, 2, 3, 4] -> [1, 3] = 2 * [1, 2] - 1
        
      return 2 * leftToRight(n / 2) - 1;
    }
};


/*

https://leetcode.com/problems/elimination-game/discuss/87128/C-1-line-solution-with-explanation

where ML(1...n) means removing elements from left to right first 
 MR(1...n) means removing elements from right to left first.

Suppoese ML(1...n) = r;
We can replace each element in array 1...n by newValue = (n + 1) - oldValue to get a new array n...1;

比如 [1,2,3,4,5,6,7,8,9] -> replace by (n + 1) - oldValue = [9,8,7,6,5,4,3,2,1]
So ML(1...n) + MR(1...n) = 1 + n

Mirroring: 
we come to the problem, suppose we have two rules:
 (1) the first elimination starts from the left side; 
 (2) the first elimination starts from the right side.
 
  We follow the same elimination rules it's just the starting point is mirrored by the center. So we have:

lastRemaining(n) + EliminateFromRightFirst(n) = n + 1;
<=> lastRemaining(n/2) + EliminateFromRightFirst(n/2) = n/2 + 1;
<=> EliminateFromRightFirst(n/2) = 1 + n/2 - lastRemaining(n/2);

For the original sequence 1,2,3,...,n, after first elimination from left side, we have a new sequence 2,4,6,...,(n-1 or n).
 The new sequence consists of even numbers. Then actually it is 2 * (1, 2, 3, ..., n/2), 
 in which the elimination for the (1, 2, 3, ... n/2) now starts from the right side. It is exactly EliminateFromRightFirst(n/2).

*/
class Solution {
public:
    int lastRemaining(int n) {
    if(n==1) return 1;
    int prev = lastRemaining(n / 2);
    return 2 * (1 + n / 2 - prev);
    }
};



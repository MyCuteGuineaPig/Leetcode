/*
Bad Question Description: 

https://leetcode.com/problems/bag-of-tokens/discuss/197856/Bad-descriptions!


Description Rewrite:

You have a bag of tokens, from which you can take whichever token you want, and after you take one, 
you can't put it back to the bag, meaning you can use every token at most once.

You start the game with P power and 0 point.

For every tokens[i], you can use it in either way:
- plus tokens[i] powers, and minus 1 point;
- or, minus tokens[i] powers, and plus 1 point.
(meaning you exchange your powers to get 1 point, or exchange your point to get more powers)

But you have to make sure that during the process, both your powers>=0 and points>=0, otherwise you would have to stop playing the game.

And you can use just some of the tokens (don't have to use all of them).

Your target is to get the maximum points possible.

*/



//2020 
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        sort(tokens.begin(), tokens.end());
        int point = 0; 
        for(int i = 0, j = tokens.size()-1; i<=j;){
            if(tokens[i] <= P){
                point++;
                P -= tokens[i++];
            }
            else if(i!=j && point > 0){ //i != j, 若只剩下一个点，不用了
                point--;
                P+= tokens[j--];
            }
            else{
                break;
            }
        }

        return point;
    }
};



class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        sort(tokens.begin(), tokens.end());
        int res = 0, points = 0, i = 0, j = tokens.size() - 1;
        while (i <= j) {
            if (P >= tokens[i]) {
                P -= tokens[i++];
                res = max(res, ++points);
            } else if (points > 0) {
                points--;
                P += tokens[j--];
            } else {
                break;
            }
        }
        return res;
    }
};


class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        sort(tokens.begin(), tokens.end());
        return helper(tokens, 0, tokens.size()-1, P, 0);
    }
    
    
    int helper(vector<int>& tokens, int i, int j, int p, int points){
        if(i > j) return points;
        int res = points;
        if(tokens[i] <= p)
            res = max(res, helper(tokens, i+1, j, p-tokens[i], points+1));
        else if(points >= 1)
            res = max(res, helper(tokens, i, j-1, p+tokens[j], points-1));
        return res;
    }
};


class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        int N = tokens.size();
        
        if (!N) return 0;
        sort(tokens.begin(), tokens.end());
        if (P < tokens[0]) return 0;
        
        int l = 0, h = N-1;
        int points = 0;
        while (l <= h) {
            if (P < tokens[l] && points) {
                P += tokens[h--]; points--;
            }
            
            if (P < tokens[l])
                return points;
            
            P -= tokens[l++];
            points++;     
        }
        return points;
    }
};
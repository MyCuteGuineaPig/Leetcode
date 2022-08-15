class Solution {
public:
    int edgeScore(vector<int>& edges) {
        vector<long>scores(edges.size(),0);
        for(int i = 0; i<edges.size(); ++i){
            scores[edges[i]] += i;
        }
        long res = 0, cnt = scores[res];
        for(int i =  0 ; i<edges.size(); ++i){
            if (scores[i] > cnt){
                res = i; 
                cnt = scores[i];
            }
        }
        return res;
    }
};

class Solution {
public:
    int edgeScore(vector<int>& edges) {
        vector<long long> score(edges.size());
        for (int i = 0; i < edges.size(); ++i)
            score[edges[i]] += i;
        return max_element(begin(score), end(score)) - begin(score);
    }
};
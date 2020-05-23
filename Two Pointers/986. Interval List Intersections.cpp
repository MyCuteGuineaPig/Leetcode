class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>>res;
        int i = 0, j = 0;
        while(i<A.size() && j < B.size()){
            if(A[i][0] < B[j][0]){
                if(A[i][1] < B[j][0])
                    ++i;
                else {
                    if(A[i][1] < B[j][1])
                        res.push_back({B[j][0], A[i++][1]});
                    else
                        res.push_back({B[j][0], B[j++][1]});
                }
            }else{
                if(B[j][1] < A[i][0])
                    ++j;
                else {
                    if(B[j][1] < A[i][1])
                        res.push_back({A[i][0], B[j++][1]});
                    else
                        res.push_back({A[i][0], A[i++][1]});
                }
            }
            
        }
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>>res;
        int i = 0, j = 0;
        while(i<A.size() && j < B.size()){
            int start  = max(A[i][0], B[j][0]);
            int end = min(A[i][1], B[j][1]);
            if(start <= end)
                res.push_back({start, end});
            
            if(A[i][1] < B[j][1]) ++i;
            else ++j;
        }
        return res;
    }
};





/*
O(M*logN) is binary search method
Since we have already O(M + N) solution, why bother to pursue the O(M*logN) solution?
Well, if M << N(or N << M), then O(M*logN) is better than O(M + N)

 */



class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        if(A.size() > B.size()){
            return intervalIntersection(B,A);
        }
        vector<vector<int>>res;
        int j = 0;
        for(int i = 0; i<A.size() && j <B.size(); ){
            int pos = findPosition(B, j, A[i][0]);
            if(pos==B.size())
                break;     
            int start  = max(A[i][0], B[pos][0]);
            int end = min(A[i][1], B[pos][1]);
            if(start <= end)
                res.push_back({start, end});
            if(A[i][1] <= B[pos][1])
                ++i;
            else 
                j = pos + 1;
        }
        return res;
    }
    
    
    int findPosition(const vector<vector<int>>&B, int l, int target){
        int r = B.size();
        while (l < r){
            int mid = l + (r-l)/2;
            if(B[mid][1] >= target)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};
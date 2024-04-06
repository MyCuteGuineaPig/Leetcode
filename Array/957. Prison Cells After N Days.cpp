class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& res, int n) {
        vector<int> tmp(8);
        vector<vector<int>> seen;
        while (n--) {
            for (int i = 1; i < 7; i++) {
                tmp[i] = res[i - 1] == res[i + 1];
            }
            if (seen.size() && seen.front() == tmp) return seen[n % seen.size()]; 
            else seen.push_back(tmp);
            res = tmp;
        }
        return res;
    }
};


class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        vector<int>ans(8);
        ans=cells;
        int m=(n-1)%14;
        while(m>=0)
        {
            for(int i=0;i<=7;i++)
            {   
                if(i==0|| i==7)
                    ans[i]=0;
                else if(cells[i-1]== cells[i+1])
                    ans[i]=1;
                else
                    ans[i]=0;
            }
            m--;
            for(int i=0;i<8;i++)
            {
                cells[i]=ans[i];
            }
        }
        return ans;
    }
};




class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        for (N = (N - 1) % 14 + 1; N > 0; --N) {
            vector<int> cells2(8, 0);
            for (int i = 1; i < 7; ++i)
                cells2[i] = cells[i - 1] == cells[i + 1] ? 1 : 0;
            cells = cells2;
        }
        return cells;
    }
};
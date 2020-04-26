class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        static const string s = "croak";
        vector<int>lookup(5);
        int result = 0;
        for(const auto& c: croakOfFrogs){
            int i = s.find(c);
            ++lookup[i];
            if(lookup[ (i - 1 + s.size())% s.size()])
                lookup[ (i - 1 + s.size())% s.size()]--;
            else if(i==0)
                ++result;
            else 
                return -1;
        }
        return result == lookup.back() ? result : -1;
    }
};

class Solution {
public:
    int minNumberOfFrogs(const string& s) {
        int table[5]; // c: 0, r: 1, o: 2, a: 3, k: 4
        memset(table, 0, sizeof(table));
        int frog = 0, maxFrog = 0;

        for(const char& c: s) {
            int i;
            switch (c) {
                case 'c': i = 0; break;
                case 'r': i = 1; break;
                case 'o': i = 2; break;
                case 'a': i = 3; break;
                case 'k': i = 4;
            }

            ++table[i];
            if (i == 0)
                maxFrog = max(maxFrog, ++frog);
            else if (--table[i - 1] < 0)
                return -1;
            else if (i == 4)
                --frog;
        }

        return frog == 0 ? maxFrog : -1;
    }
    
    
};


class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
	    // a simple trick to make it easy to count each char
        unordered_map<char, int> dict = {{'c', 0}, {'r', 1}, {'o', 2}, {'a', 3}, {'k',4}};
        
		// start iterating
        int res = 0;
        vector<int> cnt(5, 0);
        for (int i = 0; i < croakOfFrogs.size(); i++)
        {
            int cur = dict[croakOfFrogs[i]];
            if (cur > 0 && cnt[cur-1] <= cnt[cur]) // check whether it is valid
                return -1;
            cnt[cur]++;
			// update global frog max number
            res = max(cnt[0] - cnt[4], res);
        }
        
		// check if each of the count is equal to each other
        for (int i = 0; i < 4; i++)
        {
            if (cnt[i] != cnt[i+1])
                return -1;
        }
        
        return res;
    }   
};
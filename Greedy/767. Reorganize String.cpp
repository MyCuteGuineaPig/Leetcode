

/*
priority queue; 
如果有char > (size + 1)/2: return "";  size + 1是为了奇书， 比如"vvvlo" return "vovlv", v = 3 < 5/2 = 2 但是 3 >= 6/3 = 3

pq: maxheap: pop 当前最多的数，如果当前pop的char == res[-1], 跳过这个，再pop append to res

pq 最后两个char不可能相同， 不用担心出现 pq中只有(2,'a')的这种情况, 因为最多的不大于(size+1)/2
所以最坏的顺序， 我们用a表示出现最多的char, a * a * a * a * a, 

如果不判断char > (size + 1)/2: return ""， 我们可以看最后一个pq pop的char的count是不是为1(solution 2)，不为1，return "";

*/

class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> cnts;
        for (const auto& c : S) 
            ++cnts[c];
        if(any_of(cnts.begin(),cnts.end(),[&](const pair<char, int>& it){return it.second > (S.size()+1)/2;})){
            return "";
        }
        priority_queue<pair<int,char>>pq;
        for(auto it : cnts)
            pq.push(make_pair(it.second, it.first));
        string res;
        while(!pq.empty()){
            auto cur = pq.top(); pq.pop();
            if(res.empty() || cur.second != res.back()){
                res+=cur.second;
                if(--cur.first)
                    pq.push(cur);
            }else{
                auto sec = pq.top(); pq.pop();
                res += sec.second;
                if(--sec.first) pq.push(sec);
                pq.push(cur);
            }
        }
        return res;
    }
};

// Solution 2
class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> cnts;
        for (const auto& c : S) 
            ++cnts[c];
        priority_queue<pair<int,char>>pq;
        for(auto it : cnts)
            pq.push(make_pair(it.second, it.first));
        string res;
        while(pq.size()>1){ //size > 1 避免是 'aaaa' 情况，sec = pq.top() 报错
            auto cur = pq.top(); pq.pop();
            if(res.empty() || cur.second != res.back()){
                res+=cur.second;
                if(--cur.first)
                    pq.push(cur);
            }else{
                auto sec = pq.top(); pq.pop();
                res += sec.second;
                if(--sec.first) pq.push(sec);
                pq.push(cur);
            }
        }
        if(pq.top().first != 1) return "";
        return res + pq.top().second;
    }
};



//用prev 防止这次pop 和上次pop 出现同一个char
class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> cnts;
        for (const auto& c : S) 
            ++cnts[c];

        priority_queue<pair<int,char>>pq;
        for(auto it : cnts)
            pq.push(make_pair(it.second, it.first));
        string res;
        pair<int, char>prev;
        while(!pq.empty()){
            auto cur = pq.top(); pq.pop();
            if(prev.first>0) pq.push(prev);
            res+=cur.second;
            cur.first--;
            if(pq.empty() && cur.first !=0) return "";
            prev = cur;
        }
        return res;
    }
};


class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> counts;
        for (const auto& c : S) {
            ++counts[c];
        }
        if (any_of(counts.cbegin(), counts.cend(),
                  [&](const pair<char, int>& kvp) { 
                      return kvp.second > (S.length() + 1) / 2;
                  })) {
            return "";
        }

        string result;
        priority_queue<pair<int, char>> max_heap;
        for (const auto& kvp : counts) {
            max_heap.emplace(kvp.second, kvp.first);
        }
        while (max_heap.size() > 1) {
            char c1, c2;
            int count1, count2;
            tie(count1, c1) = max_heap.top(); max_heap.pop();
            tie(count2, c2) = max_heap.top(); max_heap.pop();
            result.push_back(c1);
            result.push_back(c2);
            if (count1 - 1 > 0) {
                max_heap.emplace(count1 - 1, c1);
            }
            if (count2 - 1 > 0) {
                max_heap.emplace(count2 - 1, c2);
            }
            
        }
        return max_heap.empty() ? result : result + max_heap.top().second;
    }
};



//Bucket Sort Solution
class Solution {
public:
    string reorganizeString(string S) {
        if(S.size()<2)
	{
		return S;
	}

	vector<int> counts(26, 0);
	int maxC = 1;
	int maxI = 0;
	for(auto ch : S)
	{
		counts[ch-'a']++;
		if(counts[ch-'a'] > maxC)
		{
			maxC = counts[ch-'a'];
			maxI = ch-'a';
		}
	}

	int n = S.size();
	if(maxC>(n+1)/2)
	{
		return "";
	}

	int i = 0;
	while(counts[maxI]--)
	{
		S[i] = maxI + 'a';
		i+=2; 
	}

	for(int j=0; j<26; j++)
	{
		while(counts[j]-->0)
		{
			if(i>=n)
			{
				i = 1;
			}
			S[i] = j+'a';
			i+=2;
		}
	}

	return S;
	}
};



class Solution {
public:
    string reorganizeString(string str) {
        
        int strSize = str.size();
        if(strSize < 2)
            return str;
        
        vector<int> freq(26, 0);
        int freqChar = -1, freqCharCount = -1;
        
        for(int i = 0; i < strSize; i++) {
            freq[str[i]-'a']++;
            if(freq[str[i]-'a'] > freqCharCount) {
                freqCharCount = freq[str[i]-'a'];
                freqChar = str[i]-'a';
            }
        }
        
        if(freqCharCount > (strSize+1)/2)
            return "";
        
        
        int position = 0;
        
        for(int i = -1; i < 26; i++) {
            int current = (i == -1) ? freqChar : i;
            while(freq[current]-- > 0) {
                str[position] = 'a' + current;
                position = (position+2 >= strSize) ? 1 : position+2;
            }
        }
        return str;
    }
};
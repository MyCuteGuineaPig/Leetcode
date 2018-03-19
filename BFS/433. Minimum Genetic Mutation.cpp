/*
433. Minimum Genetic Mutation.cpp

Time	Space	Difficulty
O(n * b)	O(b)	Medium

A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.
Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3


*/
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        queue<string>q;
        unordered_set<string>list(bank.begin(),bank.end());
        if(list.find(end)==list.end()) return -1;
        int dist = 1;
        q.push(start);
        while(q.size())
        {   
            int cursize = q.size();
            cout<<endl;
            for(int i = 0; i<cursize;i++){
                string top = q.front();
                q.pop();
                for(int s = 0; s<top.size(); s++){
                    char original = top[s];
                    if(original!='A'){
                        top[s] = 'A';
                        if(list.find(top)!=list.end()) {
                            if(top == end) return dist;
                            q.push(top);
                        }
                        top[s] = original;
                    }
                    if(original!='C'){
                        top[s] = 'C';
                        if(list.find(top)!=list.end()) {
                            if(top == end) return dist;
                            q.push(top);
                        }
                        top[s] = original;
                    }
                    if(original!='G'){
                        top[s] = 'G';
                        if(list.find(top)!=list.end()) {
                            if(top == end) return dist;
                            q.push(top);
                        }
                        top[s] = original;
                    }
                    if(original!='T'){
                        top[s] = 'T';
                        if(list.find(top)!=list.end()) {
                            if(top == end) return dist;
                            q.push(top);
                        }
                        top[s] = original;
                    }
                }
            }
            dist++;
        }
        return -1;
    }
};

class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string>dict(bank.begin(),bank.end());
        if(dict.find(end) == dict.end()) return -1;
        unordered_set<string>head, tail, *phead, *ptail;
        head.insert(start), tail.insert(end);
        int step = 0, n = start.size();

        while(head.size() && tail.size()){
            if(head.size()<= tail.size()){
                phead = &head;
                ptail = &tail;
            }else{
                phead = &tail;
                ptail = &head;
            }
            unordered_set<string>tmp;
            step++;
            for(auto itr = phead->begin(); itr!=phead->end(); itr++){
                for(int i = 0; i<n; i++){
                    string dna = *itr;
                    for(auto g: string("ATGC")){
                        dna[i] = g;
                        if(ptail->find(dna) != ptail->end()) return step;
                        if(dict.find(dna)!=dict.end()){
                            tmp.insert(dna);
                            dict.erase(dna);
                        }
                    }
                }
            }
            *phead = tmp;//*phead 是phead 指代的对象，whether tail/head 等于temp
            /*
            这句话等于：
            if(head.size()<= tail.size())
                head = tmp;
            else 
                tail = tmp;
            
            */
        }
        return -1;
    }
};
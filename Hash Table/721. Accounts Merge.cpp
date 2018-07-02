/*
721. Accounts Merge

Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, 
and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. 
Note that even if two accounts have the same name, they may belong to different people as people could have the same name. 
A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, 
and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

Example 1:
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
Note:

The length of accounts will be in the range [1, 1000].
The length of accounts[i] will be in the range [1, 10].
The length of accounts[i][j] will be in the range [1, 30].

*/


/*
Union set:  例子会忽略名字直接拿number suffix作为整个list的representation

定义：  
直接parent:  比如 0->3, 3->1, 1->1,  0的直接parent是3, 3的直接parent是1
间接parent:  比如 0->3, 3->1, 1->1,  0的间接parent是1, 
最终parent:  比如 0->3, 3->1, 1->4, 4->4, 0的最终parent是4， 最终parent是当做dfs到头，parent的map的key = value,

需要数据结构:
parent: 用来储存每个acct[i][j]的直接parent
owner： 用在最后结果，把acct[i][j] 的邮件对上它的名字
unionset: 用来把每个acc[i][j]的最终parent，对上一个set，set里面是这个parent的email 集合

[["David","David0@m.co","David4@m.co","David3@m.co"],
["David","David5@m.co","David5@m.co","David0@m.co"]] 

用上面的例子  
1. 找组内parent，loop account找每个acct[i][j] 的直接parent，直接parent设为acct[i][1], 

2. 找组间parent, loop account，找acct[i][1]的parent 并设为p，把p设为整个i组的parent
    - 到每个acct[i][j]，找到这个acct[i][j]的parent为p2，把p2的parent设为p，上面例子结果如果下，
      4 -> 0, 3->0 ; 5 -> 5 0 - > 5
    a.  这样找间接parent，可能把acct[i][j] 连上他们的间接parent,这用情况出现是acct[i][1]之前出现过，直接parent不是他们自己，
        而acct[i][j] 没有之前出现过，parent是step1设的直接parent acct[i][1]
        比如下面例子  5->3 
        [["David","D0@m.co","D5@m.co"],
        ["David","D5@m.co","D3@m.co"]] 
    b.  或者把acct[i][j]的间接parent连上p(parent连上大的parent)，这用情况出现是acct[i][j]之前出现过，直接parent不是他们自己，
        这样找acct[i][j]的parent返回的是他们间接或直接parent p2, 把p2 -> 连上当前的p
        比如 i = 0:  5->0; i=1: 5->3(acct[1][2]的parent是5,当前p是3) ;
        map为 0->5, 5->3, 3->3
        [["David","D5@m.co","D0@m.co"],
        ["David","D3@m.co","D0@m.co"]] 
    

3. 找最终parent，第二步已经把所有组间的间接parent找到，此时已经获得所有的间接parent，
    再loop每个acct[i][j]，找他们的最终parent p3，再他们最终unionset[p3]下面的set 插入acct[i][j]
然后在acct之前找parent


第一次找parent时候，要把acct[i][1]找parent 作为整个list的parent。如果不找acct[i][1]的parent，直接拿acct[i][1]，
会在unionset find的时候有runtime error!!!
比如
[["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe2@m.co"],["Gabe","Gabe3@m.co","Gabe4@m.co","Gabe2@m.co"]]
如果直接拿acct[i][1]作为parent，
当 i = 0, p=0  0->0, 3->0, 2->0
当 i = 1, p=3, 3->3  4->3, 0(0是2的parent)->3,  

这样有个loop  3->0,  0->3, 而出现原因是当i=0时，已经出现了3->0
当i=1时，3的parent应该是0，但是我们忽略了0，直接拿3作为parent，而此时有2出现，2的parent是0， 这样把0就assign给了3
如果拿3的parent 0作为整个acct[1]的parent，此时 0(0是2的parent)-> 0

*/

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string,string>parent;
        unordered_map<string,string>name;
        unordered_map<string, set<string>>unionset;
        for(auto& acct: accounts){
            for(int j =1; j<acct.size();j++){
                parent[acct[j]] = acct[1];
                name[acct[j]] = acct[0];
            }
        }
        
        for(auto& acct: accounts){
            string p = find(acct[1],parent);
            parent[acct[1]] = p;
            for(int i = 2; i<acct.size(); i++){
                parent[find(acct[i],parent)] = p;   
            }
        }
        
        for(auto& acct: accounts){
            for(int i = 1; i<acct.size(); i++){  
                unionset[find(acct[i],parent)].insert(acct[i]);   
            }
        }
        
        vector<vector<string>>res;
        for(auto it: unionset){
            vector<string>temp(it.second.begin(),it.second.end());   
            temp.insert(temp.begin(),name[it.first]);
            res.push_back(temp);
        }
        return res;
    }
    
    
    string find(string s, unordered_map<string,string>&parent){
        return parent[s] == s ? s : find(parent[s], parent);
    }
};




/*
Disjoint Set Union Find

需要数据结构:
id: 用来储存每个acct[i][j]的对于它在Disjoint set中的id
name: 用在最后结果，把acct[i][j] 的邮件对上它的名字
lookup: 用来把每个acc[i][j]的最终parent，对上一个set，set里面是这个parent的email 集合


跟上面方法不同的是，给每个acct[i][j]一个id，id存在unordered_map的数据结构中，每次union find的时候是把他们的id merge
比如 5->0,  0->3, 3->3, 在DisjointSet的find结束之后 5->3, 0->3, 3->3;  

1. loop acct，给每个acct[i][j] 一个id，然后组内（同时也是找现在最终的parent）,find() 让每一个node 都连上现在的最终parent
    比如 5->3, 现在出现 union(5,2), find 5 parent是3，得到 5->2, 3->2; 改了之前建立的parent
    ***
    现在最终parent: 因为可能最后最终parent 会稍晚出现，比如 现在有链 9->7->5, 现在要union (5,3), 5->3, 
    但是9，7的parent 还是5，所以需要step2，找最后最终parent
    ***

2. loop acct, 根据name的key找每个key的最后最终parent，根据key找的好处，是跳过重复的，因为可能某个name会出现多次
    把最后最终parent的作为key，插入当前email到lookup下的set



每次都是找最终的parent，然后把最终的parent 的id

*/

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string,int>id;
        unordered_map<string,string>name;
        unordered_map<int, set<string>>lookup;
        vector<vector<string>>res;
        DisjointSet union_find;
        
        for(auto& acct: accounts){
            for(int i = 1; i<acct.size(); i++){
                if(id.find(acct[i]) == id.end()){
                    id[acct[i]] = union_find.getID();
                    name[acct[i]] = acct[0];
                }
                union_find.union_set(id[acct[1]], id[acct[i]]);
            }
        }
        
        for(auto it: name){
            int key_id = union_find.find(id[it.first]);
            lookup[key_id].insert(it.first);
        }
        
        for(auto& it: lookup){
            vector<string>temp;
            string curname = name[*it.second.begin()];
            temp.push_back(curname);
            for(auto e: it.second){
                temp.push_back(e);
            }
            res.push_back(move(temp));
        }
        return res;
    }
    
    
    struct DisjointSet{
        int index;
        vector<int>set;
        DisjointSet() {index = 0;}
        
        int getID(){
            set.push_back(index);
            return index++;
        }
        
        int find(int num){
            if(set[num]!=num){
                set[num] = find(set[num]);
            }
            return set[num];
        }
        
        void union_set(int a, int b){
            int a_root = find(a), b_root = find(b);
            set[max(a_root,b_root)] = set[min(a_root,b_root)];
        }
    };
};



/*
DFS 的解：
给每个account[i][j] 先assign一个id i，然后loop acct， 如果acct[i]已经visit过，就跳过
否则loop acct[i]的每一个元素，看acct[i][j]是否在别的acct[k] where k!=i出现过，如果出现，再loop别的account[k]，
一遍loop 一边push acct[i][j]进result

We give each account an ID, based on the index of it within the list of accounts.

[
["John", "johnsmith@mail.com", "john00@mail.com"], # Account 0
["John", "johnnybravo@mail.com"], # Account 1
["John", "johnsmith@mail.com", "john_newyork@mail.com"],  # Account 2
["Mary", "mary@mail.com"] # Account 3
]
Next, build an emails_accounts_map that maps an email to a list of accounts, which can be used to track which email is linked to which account.
 This is essentially our graph.

# emails_accounts_map of email to account ID
{
  "johnsmith@mail.com": [0, 2],
  "john00@mail.com": [0],
  "johnnybravo@mail.com": [1],
  "john_newyork@mail.com": [2],
  "mary@mail.com": [3]
}


*/

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        vector<int>visited(n,0);
        unordered_map<string,vector<int>>lookup;
        vector<vector<string>>res;
        for(int i = 0; i<n; i++){
            for(int j = 1; j<accounts[i].size(); j++){
                lookup[accounts[i][j]].push_back(i);
            }
        }
        for(int i = 0; i<n; i++){
            if(visited[i]) continue;
            set<string>cur;
            DFS(cur, accounts, visited, lookup, i);
            vector<string>temp;
            temp.push_back(accounts[i][0]);
            for(auto it: cur){
                temp.push_back(it);
            }
            res.push_back(temp);
        }
        return res;
        
    }
    
    void DFS(set<string>&cur, vector<vector<string>>& accounts, vector<int>& visited, unordered_map<string,vector<int>>&lookup, int index){
        if(visited[index]) return;
        visited[index] = 1;
        for(int i = 1; i<accounts[index].size(); i++){
            cur.insert(accounts[index][i]);
            for(auto next: lookup[accounts[index][i]]){
                if(next!=index && !visited[next])
                    DFS(cur, accounts, visited, lookup, next);
            }
        }
    }
};

class Solution(object):
    def accountsMerge(self, accounts):
        from collections import defaultdict
        visited_accounts = [False] * len(accounts)
        emails_accounts_map = defaultdict(list)
        res = []
        # Build up the graph.
        for i, account in enumerate(accounts):
            for j in range(1, len(account)):
                email = account[j]
                emails_accounts_map[email].append(i)
        # DFS code for traversing accounts.
        def dfs(i, emails):
            if visited_accounts[i]:
                return
            visited_accounts[i] = True
            for j in range(1, len(accounts[i])):
                email = accounts[i][j]
                emails.add(email)
                for neighbor in emails_accounts_map[email]:
                    dfs(neighbor, emails)
        # Perform DFS for accounts and add to results.
        for i, account in enumerate(accounts):
            if visited_accounts[i]:
                continue
            name, emails = account[0], set()
            dfs(i, emails)
            res.append([name] + sorted(emails))
        return res
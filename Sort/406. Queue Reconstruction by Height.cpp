/*
406. Queue Reconstruction by Height

Suppose you have a random list of people standing in a queue.
 Each person is described by a pair of integers (h, k), where h is the height of the person 
 and k is the number of people in front of this person who have a height greater than or equal to h.
  Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.


Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

*/

/*
Insertion 
Complexity: O(n)
space: O(n)
先把大的安排了，再安排小的
*/

class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(),people.end(),[](pair<int, int> p1, pair<int, int> p2){
            return p1.first > p2.first || (p1.first==p2.first && p1.second < p2.second);
        });
        vector<pair<int,int>>res;
        for(auto i: people)
            res.insert(res.begin()+i.second,i);
        return res;
    }
};


/*

// Time:  O(n * sqrt(n))
// Space: O(n)

*/
class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), 
            [](const pair<int, int>& a, pair<int, int>& b) {
                return b.first == a.first ? a.second < b.second : b.first < a.first;
            });

        vector<vector<pair<int, int>>> blocks(1);
        for (const auto& p : people) {
            auto index = p.second;
            int i = 0;
            for (; i < blocks.size(); ++i) {
                if (index <= blocks[i].size()) {
                    break;
                }
                index -= blocks[i].size();
            }
            cout<<" cur p "<<p.first<<" sec "<<p.second<<"  ipos "<<i<<endl;
            blocks[i].insert(blocks[i].begin() + index, p);
            
            if (blocks[i].size() * blocks[i].size() > people.size()) {
                cout<<" bigger than size  "<<blocks[i].size()<<" i "<<i<<endl;
            
                blocks.emplace(blocks.begin() + i + 1,
                               blocks[i].begin() + blocks[i].size() / 2,
                               blocks[i].end());
                /*

                    或者用blocks.insert(blocks.begin() + i + 1,
                               {blocks[i].begin() + blocks[i].size() / 2,
                               blocks[i].end()});
                */
                blocks[i].erase(blocks[i].begin() + blocks[i].size() / 2, blocks[i].end());
                cout<<" new block ";
                for(int i = 0; i<blocks.size();i++){
                    cout<<" cur_i " <<i<<"  ";
                    for(auto j: blocks[i])
                        cout<<" ( "<<j.first<<", "<<j.second<<"), ";
                    cout<<endl;
                }
            }
        }

        vector<pair<int, int>> result;
        for (const auto& block : blocks) {
            for (const auto& p : block) {
                result.emplace_back(p);
            }
        }
        return result;
    }
};



class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(),people.end(),[](pair<int, int> p1, pair<int, int> p2){
            return p1.first > p2.first || (p1.first==p2.first && p1.second < p2.second);
        });
        vector<pair<int,int>>res;
        vector<vector<pair<int,int>>>blocks(1);
        for(auto p: people){
            int index = p.second;
            int i = 0;
            for(;i<blocks.size();i++){
                if(index<=blocks[i].size()) break;
                index -= blocks[i].size();
            }
            blocks[i].insert(blocks[i].begin()+index,p);
            if(blocks[i].size()*blocks[i].size()>people.size()){//让每一个bucket都不超过sqrt个元素，这样保证每次insert 都不超过sqrt(n)
                blocks.emplace(blocks.begin()+i+1, blocks[i].begin()+blocks[i].size() / 2, blocks[i].end()); 
                blocks[i].erase( blocks[i].begin()+blocks[i].size() / 2, blocks[i].end());
            }
        }
        for(auto block: blocks)
            for(auto b: block)
                res.push_back(b);
        return res;
    }
};



/*
O(n^2)
*/
class Solution {
    static bool shorter(pair<int,int> p1,pair<int,int> p2){
        return (p1.first<p2.first)||(p1.first==p2.first && p1.second>p2.second);
    }
    
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(),people.end(),shorter);//sort people queue based on h.

       
        for(int i=people.size()-1;i>=0;i--)
        {
            //cout<<people[i].first<<"-"<<people[i].second<<endl;
            if(people[i].second>0){
                pair<int,int> temp = people[i];
                for(int dt=0;dt<temp.second;dt++){
                    people[i+dt] = people[i+dt+1];
                }
                people[i+temp.second] = temp;
            }
        }
        return people;
    }
};
/*
[[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]

7-0
 after (4,4), (5,2), (5,0), (6,1), (7,1), (7,0), 
7-1
 after (4,4), (5,2), (5,0), (6,1), (7,0), (7,1), 
6-1
 after (4,4), (5,2), (5,0), (7,0), (6,1), (7,1), 
5-0
 after (4,4), (5,2), (5,0), (7,0), (6,1), (7,1), 
5-2
 after (4,4), (5,0), (7,0), (5,2), (6,1), (7,1), 
4-4
 after (5,0), (7,0), (5,2), (6,1), (4,4), (7,1), 


*/


//for each element, others that are shorter are 'invisible'
//ascending order,every k is zero
// 1 2 3 4 7 7 7
// 0 0 0 0 2 1 0

// 7 6 5 4 3 2 1
// 0 1 2 3 4 5 6

// 2 3 1 7 4 6 5
// 0 0 2 0 1 1 2

// 1 2 3 7 4 6 5
// 0 0 0 0 1 1 2
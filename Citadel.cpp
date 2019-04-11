	/*
  
    only two moves in one direction, and one move in another direction. 
    e.g. from 1, only can move to 6 or 8; 
    
    move exactly 10 times, how many possible ways to move to 9
  
    1 2 3 
    4 5 6
    7 8 9
      0
  
  */
  
  
  int main(){
    unordered_map<int, vector<int>>nextmove = { {1,{6,8}},{2,{7,9}},{3,{4,8}},{4,{3,9,0}},{6,{1,0,7}}, {7,{2,6}},{8,{1,3}},{9,{4,2}},{0,{4,6}} };

    unordered_map<int, int>cur;
    cur[1] = 1;
    for (int z = 0; z < 10; z++) {
      unordered_map<int, int>nextmp;
      for (auto i : cur) {
        for (auto next : nextmove[i.first]) {
          nextmp[next] += i.second;
        }
      }
      cur = nextmp;
    }
    cout << cur[9] << endl;
    system("pause");
    return 0;
  }

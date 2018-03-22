/*
282. Expression Add Operators

Time	Space	Difficulty	
O(4^n)	O(n)	Hard

Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples: 
"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

*/

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string>res;
        dfs(num,target,res,"", 0, 0, 0);
        return res;
    }

    /**
     * cur is the string with operand till now 
     * pos is the current position
     * cv is the cumulative sum till pos 
     * pv is the old sum (just previous two number with a operator sum)
     * 
    */
    void dfs(const string & num,  const int & target, vector<string>&res, string cur, long pos, long cv, long pv){
        
        if(pos == num.size() && cv == target){
            //cout<<"insert "<<cv<<" cur "<<cur<<endl;
            res.push_back(cur);
        }
        else{
            //cout<<"cur "<<cur<<" cv "<<cv<<" pv "<<pv <<endl;
            for(int i = pos; i<num.size(); i++){
                string substr = num.substr(pos,i-pos+1);
                //cout<<"   n "<<n<<" substr "<<substr<<endl;
                if(i-pos>=1 && substr[0] == '0') continue;
                long n = stol(substr);
                //cout<<"  contn "<<n<<" substr "<<substr<<" i "<<i<<" pos "<<pos<<endl;
                if(pos == 0)
                {
                    dfs(num, target,res, substr, i+1, n, n);
                }
                else{
                    dfs(num, target,res, cur+'+'+substr, i+1, cv+n, n);
                    dfs(num, target,res, cur+'-'+substr, i+1, cv-n, -n);
                    //cout<<"   cur+'*' "<<cur+'*'+substr<<" cv "<<cv<<"  pv "<<pv << " sum "<<cv-pv + pv*n<<" nowpv "<<pv*n<<endl;
                    dfs(num, target,res, cur+'*'+substr, i+1, cv-pv + pv*n, pv*n);
                }

            }
        }
    }
};
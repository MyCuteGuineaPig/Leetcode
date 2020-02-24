class Solution {
public:
    vector<int> closestDivisors(int x) {
        for (int a = sqrt(x + 2); a > 0; --a) {
            if ((x + 1) % a == 0)
                return {a, (x + 1) / a};
            if ((x + 2) % a == 0)
                return {a, (x + 2) / a};
        }
        return {};
    }
};

class Solution {
public:
    int largestDivisor(int num) {
        int d = sqrt(num);
        while (num % d != 0) --d;
        return d;
    }
    vector<int> closestDivisors(int num) {
        auto d1 = largestDivisor(num + 1), d2 = largestDivisor(num + 2);
        if (abs(d1 - (num + 1) / d1) < abs(d2 - (num + 2) / d2))
            return {d1, (num + 1) / d1};
        return { d2, (num + 2) / d2 };
    }
};



class Solution {
public:
    vector<int> closestDivisors(int num) 
    {
        int num1=num+1,num2=num+2,dist=INT_MAX;
        vector<int> result;
        for(int i=sqrt(num2);i>=1;i--)
            if(num2%i==0)	//Check if `i` is a factor.
            {
                result={i,num2/i};
		dist=num2/i-i;
                break;
            }
        for(int i=sqrt(num1);i>=1;i--)
	    if(num1%i==0) //Check the combination if `i` is a factor.
            {
                if(num1/i-i<dist)    //Check if this combination is closer than current result.
                    result={i,num1/i};
                break;
            }
        return result;
    }
};
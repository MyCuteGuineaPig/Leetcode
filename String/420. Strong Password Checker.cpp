/*
420. Strong Password Checker

A password is considered strong if below conditions are all met:

It has at least 6 characters and at most 20 characters.
It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is strong, 
assuming other conditions are met).
Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change required to make s a strong password. 
If s is already strong, return 0.

Insertion, deletion or replace of any one character are all considered as one change.



*/


/*
解题思路: 
如果长度小于6,  
    - 如果有重复的插入元素在 第二个第三个元素中间，比如aaaa, 变成aabaa
    - 对比插入的长度+替代的(e.g aaaaa, % 3 =2, replace变为aabaa, replace += 5 /3 = 1)， 和大写 + 小写 + 数字，因为大写，小写， 数字也算是replace

如果长度在6 和20之间, 
    - 可以直接replace, 不用删除, 也不用add, 直接替换 (长度/3) 比如aaaa, 换成abaa or aaba,  比如aaaaa, 换成aabaa

如果长度在20以上，
    -  考虑删除，先删除元素，让他的长度变成 %3 =2 (除以3余0,删一个, 除以3余1, 删2个 比如aaaaaaaaaa(长度为10，先删除两个，让它长度变8)), 这样需要的步数最小
       比如aaaaaa(len = 6), 删除一个变成 aaaaa, 这样直接替换aabaa， replace = 1, delete = 1
    -  如果最后需要删除的个数不满足( toDel - del > 0), 与其replace,不如就直接删除, 因为删除要三个三个删除，删除的个数+3, 替代额个数减去1
         比如aabaa， 用b替代了一个a，但是删除的话，直接删除aab
    -  如果发现删除的删除多了，我们要把删多的，再还给替代的，比如删除了两个a, 还给替代的，可以直接还zy, 不还aa从而不会构成三个重复的

*/




class Solution {
public:
    int strongPasswordChecker(string s) {
        int n = s.size();
        int upper = 1, lower = 1, digit = 1;
        int toAdd = max(0, 6 - n);
        int toDel = max(0, n - 20);
        int rep = 0, add = 0, del = 0;
        // use to store consecutive letters based on len % 3
        // because lower value of len % 3 has precedence than
        // larger one on impact of reducing replacement number
        // len % 3 = 0, 1 deletion = 1 replacement aaa -> aa
        // len % 3 = 1, 2 deletion = 1 replacement aaaa -> aa
        // len % 3 = 2, 3 deletion = 1 replacement aaaaa -> aa
        // our goal is to use limited deletions to reduce
        // necessary replacement as many as possible
        vector<vector<int>> repeats(3);
        int j = 0;
        for (int i = 0; i <= n; i++) {
            if (i == n || s[i] != s[j]) {
                int len = i - j;
                if (i - j > 2) {
                    repeats[len % 3].push_back(len);
                }
                j = i;
            }
            if (i == n) break;
            if (isdigit(s[i])) digit = 0;
            if (isupper(s[i])) upper = 0;
            if (islower(s[i])) lower = 0;
        }

        for (int i = 0; i < 3; i++) {
            auto v = repeats[i];
            for (int j = 0; j < v.size(); j++) {
                if (i < 2) {
                    if (toAdd - add > 0) { // current length less than 6
                        add++;
                        v[j] -= i+1;
                    }
                    if (toDel - del > 0) { // current length larger than 20
                        del += i+1; // del could be larger than 'toDel' which will be made up below 
                        v[j] -= i+1;
                    }
                }
                rep += v[j] / 3;
            }
        }
        if (toDel - del > 0) {
            /* after v[j] -= i+1; in the for loop above, the length of all consecutive letters
            * handled by rep += v[j] / 3; meets len % 3 = 2, for example:
            * case len % 3 = 0 : "aaaaaa" => "aaaaa", rep get 1 credit via rep += v[j] / 3;
            * case len % 3 = 1 : "aaaaaaaaaa" => "aaaaaaaa", rep get 2 credits via rep += v[j] / 3;
            * now, there could be more letters to delete, i.e. toDel - del > 0
            * so, we need to take the credit given to rep back
            * because at the time rep got the credit, len % 3 is 2, to reduce 1 rep, we need to
            * do 3 deletions, that is how the number '3' comes out. 
            * certainly, if rep didn't get enough credits, we shouldn't overdraw, i.e. minimum rep
            * should be 0.
            */
            rep = max(0, rep - (toDel - del) / 3);//还有更多的需要delete的, 所以不用与其替换一个，不如delete 3个
        }
        else {
            rep += del - toDel; // make up. del - toDel could only be 0 or 1， 不用删除那么多，把删除的都替换回来
        }

        return toDel + max(toAdd + rep, upper + lower + digit);
    }
};





class Solution {
public:
    int strongPasswordChecker(string s) {
        int deleteTarget = max(0, (int)s.length() - 20), addTarget = max(0, 6 - (int)s.length());
        int toDelete = 0, toAdd = 0, toReplace = 0, needUpper = 1, needLower = 1, needDigit = 1;
        
        ///////////////////////////////////
        // For cases of s.length() <= 20 //
        ///////////////////////////////////
        for (int l = 0, r = 0; r < s.length(); r++) {
            if (isupper(s[r])) { needUpper = 0; }               
            if (islower(s[r])) { needLower = 0; }
            if (isdigit(s[r])) { needDigit = 0; }
            
            if (r - l == 2) {                                   // if it's a three-letter window
                if (s[l] == s[l + 1] && s[l + 1] == s[r]) {     // found a three-repeating substr
                    if (toAdd < addTarget) { toAdd++, l = r; }  // insert letter to break repetition if possible
                    else { toReplace++, l = r + 1; }            // replace current word to avoid three repeating chars
                } else { l++; }                                 // keep the window with no more than 3 letters
            }
        }
        if (s.length() <= 20) { return max(addTarget + toReplace, needUpper + needLower + needDigit); }
        
        //////////////////////////////////
        // For cases of s.length() > 20 //
        //////////////////////////////////
        toReplace = 0;                                          // reset toReplace
        vector<unordered_map<int, int>> lenCnts(3);             // to record repetitions with (length % 3) == 0, 1 or 2
        for (int l = 0, r = 0, len; r <= s.length(); r++) {     // record all repetion frequencies
            if (r == s.length() || s[l] != s[r]) {
                if ((len = r - l) > 2) { lenCnts[len % 3][len]++; } // we only care about repetions with length >= 3
                l = r;
            }
        }
        
        // use to store consecutive letters based on len % 3
        // because lower value of len % 3 has precedence than
        // larger one on impact of reducing replacement number
        // len % 3 = 0, 1 deletion = 1 replacement aaa -> aa
        // len % 3 = 1, 2 deletion = 1 replacement aaaa -> aa
        // len % 3 = 2, 3 deletion = 1 replacement aaaaa -> aa
        /*
            Use deletions to minimize replacements, following below orders:
            (1) Try to delete one letter from repetitions with (length % 3) == 0. Each deletion decreases replacement by 1
            (2) Try to delete two letters from repetitions with (length % 3) == 1. Each deletion decreases repalcement by 1
            (3) Try to delete multiple of three letters from repetions with (length % 3) == 2. Each deletion (of three 
            letters) decreases repalcements by 1
        */
        for (int i = 0, numLetters, dec; i < 3; i++) {                
            for (auto it = lenCnts[i].begin(); it != lenCnts[i].end(); it++) {
                if (i < 2) {  //aaaaaa numletters = 2, 1, 12/3 = 4 
                    numLetters = i + 1, dec = min(it->second, (deleteTarget - toDelete) / numLetters);
                    toDelete += dec * numLetters;               // dec is the number of repetitions we'll delete from
                    it->second -= dec;                          // update number of repetitions left
                    
                    // after letters deleted, it fits in the group where (length % 3) == 2
                    if (it->first - numLetters > 2) { lenCnts[2][it->first - numLetters] += dec; }   
                }
                
                // record number of replacements needed
                // note if len is the length of repetition, we need (len / 3) number of replacements
                toReplace += (it->second) * ((it->first) / 3);  
            }    
        }

        int dec = (deleteTarget - toDelete) / 3;                // try to delete multiple of three letters as many as possible
        toReplace -= dec, toDelete -= dec * 3;
        return deleteTarget + max(toReplace, needUpper + needLower + needDigit);
    }
};
/*
424. Longest Repeating Character Replacement


Given a string that consists of only uppercase English letters, 
you can replace any letter in the string with another letter at most k times. 
Find the length of a longest substring containing all repeating letters you can get after performing the above operations.

Note:
Both the string's length and k will not exceed 104.

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.

*/


/*
This solution is great, best so far. However, it requires a bit more explanation.

Since we are only interested in the longest valid substring, our sliding windows need not shrink, 
even if a window may cover an invalid substring.
 We either grow the window by appending one char on the right, 
 or shift the whole window to the right by one. 
 And we only grow the window when the count of the new char exceeds the historical max count 
 (from a previous window that covers a valid substring).

That is, we do not need the accurate max count of the current window; 
we only care if the max count exceeds the historical max count; and that can only happen because of the new char.

*/

/*

Awesome solution, but it needs some more detailed explanation.
Many people know the problem can be reiterated as :
"longest substring where (length - max occurrence) <= k"
The key point is we are focusing on "longest".
So assume we initially found a valid substring, what do we do next?

Still valid even appended by one more char——then we are happy, just expand the window
It became invalid. But at this time, do we have to shrink the window?
——No, we shift the whole window rightwards by one unit. So that the length is unchanged.
The reason for that is , any index smaller than original "start", 
will never have the chance to lead a longer valid substring than current length of our window.
Do we need to update max in time?
——No. Once again, we focus on "longest". The length of valid substring is determined by what?
Max Occurrence + k
We only need to update max occurrence when it becomes larger, because only that can we generate a longer valid substring.
If we can't surpass the historic max occurrence, then we can not generate a longer valid substring from current "start", 
I mean the new windows's left bound. To some extend, this becomes a game to find max occurrence.
Or , a better understanding is:
"A game to eliminate inferior 'left bounds'.
*/


/*

*/
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int>count(128);
        int res=0;
        int start=0;
        for(int end=0; end<s.length(); end++)
        {
            res = max(res, ++count[s[end]]);
            cout<<res<<" res "<<" end "<<end<<" s[end] "<<s[end]<<" start "<<start<<" s[start ] "<<start<<" end-start "<<end-start<<" res+k "<<res+k<<endl;
            if(res+k<=end-start){
                count[s[start]]--;
                start ++;
                cout<<" count[s[start]]-- "<<count[s[start]]<<" start "<<start<<endl;
            }
        }
        return s.length()-start;
    }
};
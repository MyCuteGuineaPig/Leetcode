/*
388. Longest Absolute File Path



Suppose we abstract our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext
The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. 
subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. 
For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", 
and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, 
return the length of the longest absolute path to file in the abstracted file system. 
If there is no file in the system, return 0.

Note:
The name of a file contains at least a . and an extension.
The name of a directory or sub-directory will not contain a ..
Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.


*/


//"\n", "\t", "\123" will all be count the length as one

/*
第几层有几个\t
比如\t\t\tfile2.ext 是第三层
*/


class Solution {
public:
    int lengthLongestPath(string input) {
        input.push_back('\n');
        int start = 0, res = 0;
        unordered_map<int,int>map;
        for(int i = input.find("\n"); i!=string::npos; start = i+1, i = input.find("\n",i+1)){
            int s2 = input.find_first_not_of('\t',start);
            int depth = s2 - start;
            int len = i - s2;
            if(find(input.begin()+s2, input.begin()+i,'.')!=input.begin()+i){
                res = max(res, map[depth] + len);
            }else{
                map[depth+1] = map[depth] + len+1;//包括/, 比如\n\t\t算一个
            }
        } 
        return res;
    }
};


class Solution {
public:
    int lengthLongestPath(string input) {
        int res = 0;
        istringstream ss(input);
        unordered_map<int, int> m{{0, 0}};
        string line = "";
        while (getline(ss, line)) {
            int level = line.find_last_of('\t') + 1;
            int len = line.substr(level).size();
            if (line.find('.') != string::npos) {
                res = max(res, m[level] + len);
            } else {
                m[level + 1] = m[level] + len + 1;
            }
        }
        return res;
    }
};

class Solution {
public:
    int lengthLongestPath(string input) {
        input.push_back('\n');

        size_t max_len = 0;
        unordered_map<int, int> path_len;
        path_len[0] = 0;

        for (auto i = input.find("\n"), prev_i = 0ul;
             i != string::npos;
             prev_i = i + 1, i = input.find("\n", i + 1)) {

            const auto line = input.substr(prev_i, i - prev_i);
            const auto name = line.substr(line.find_first_not_of("\t"));
            const auto depth = line.length() - name.length();
            cout<<"line "<<line<<" name "<<name<<" depth "<<depth<<endl;
            if (name.find('.') != string::npos) {
                max_len = max(max_len, path_len[depth] + name.length());
            } else {
                path_len[depth + 1] = path_len[depth] + name.length() + 1;
            }
        }
        return max_len;
    }
};
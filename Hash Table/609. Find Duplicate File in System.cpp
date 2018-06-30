/*
609. Find Duplicate File in System


Given a list of directory info including directory path, and all the files with contents in this directory, 
you need to find out all the groups of duplicate files in the file system in terms of their paths.

A group of duplicate files consists of at least two files that have exactly the same content.

A single directory info string in the input list has the following format:

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm. 
Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.

The output is a list of group of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. 
A file path is a string that has the following format:

"directory_path/file_name.txt"

Example 1:
Input:
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
Output:  
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
Note:
No order is required for the final output.
You may assume the directory name, file name and file content only has letters and digits, and the length of file content is in the range of [1,50].
The number of files given is in the range of [1,20000].
You may assume no files or directories share the same name in the same directory.
You may assume each given directory info represents a unique directory. Directory path and file info are separated by a single blank space.
Follow-up beyond contest:
Imagine you are given a real file system, how will you search files? DFS or BFS?
If the file content is very large (GB level), how will you modify your solution?
If you can only read the file by 1kb each time, how will you modify your solution?
What is the time complexity of your modified solution? What is the most time-consuming part and memory consuming part of it? How to optimize?
How to make sure the duplicated files you find are not false positive?
*/


class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string,vector<string>>map;
        string temp;
        for(auto path:paths){
            stringstream ss(path);
            getline(ss, temp, ' ');
            string root = temp;
            while(getline(ss, temp, ' ')){
                size_t pos = temp.find('(');
                string file = temp.substr(0,pos);
                string content = temp.substr(pos,temp.length()-pos-1);
                map[content].push_back(root+"/"+file);
            }
        }
        vector<vector<string>>res;
        for(auto it: map){
            if(it.second.size()>1){
                res.push_back(it.second);
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> m;
        for (const auto& path : paths) {
            size_t i = path.find(' ');
            string directory = path.substr(0, i);
            while (true) {
                size_t j = path.find(' ', i + 1);
                string file = path.substr(i + 1, j - i - 1);
                size_t k = file.find('(');
                string fileName = file.substr(0, k);
                string fileContent = file.substr(k + 1, file.size() - k - 2);
                m[fileContent].push_back(directory + '/' + fileName);
                if (j == string::npos) {
                    break;
                }
                i = j;
            }
        }
        vector<vector<string>> res;
        for (const auto& p : m) {
            if (p.second.size() >= 2) {
                res.push_back(p.second);
            }
        }
        return res;
    }
};

/*
Follow up questions:

1. Imagine you are given a real file system, how will you search files? DFS or BFS ?
In general, BFS will use more memory then DFS. However BFS can take advantage of the locality of files in inside directories, and therefore will probably be faster

2. If the file content is very large (GB level), how will you modify your solution?
In a real life solution we will not hash the entire file content, since it's not practical. Instead we will first map all the files according to size. 
Files with different sizes are guaranteed to be different. We will than hash a small part of the files with equal sizes (using MD5 for example).
Only if the md5 is the same, we will compare the files byte by byte

3. If you can only read the file by 1kb each time, how will you modify your solution?
This won't change the solution. We can create the hash from the 1kb chunks, and then read the entire file if a full byte by byte comparison is required.

What is the time complexity of your modified solution? What is the most time consuming part and memory consuming part of it? How to optimize?
Time complexity is O(n^2 * k) since in worse case we might need to compare every file to all others. k is the file size

How to make sure the duplicated files you find are not false positive?
We will use several filters to compare: File size, Hash and byte by byte comparisons.




MD5 is definitely one way to hash a file, another more optimal alternative is to use SHA256.

Also, to answer this What is the most time consuming part and memory consuming part of it? How to optimize? part:
Comparing the file (by size, by hash and eventually byte by byte) is the most time consuming part.
Generating hash for every file will be the most memory consuming part.
We follow the above procedure will optimize it, since we compare files by size first, only when sizes differ, 
we'll generate and compare hashes, and only when hashes are the same, we'll compare byte by byte.
Also, using better hashing algorithm will also reduce memory/time.


*/

/*
In preparing for my Dropbox interview, I came across this problem and really wanted to find the ideas behind the follow up questions 


To find duplicate files, given input of String array is quite easy. Loop through each String and keep a HashMap of Strings to Set/Collection of Strings: 
mapping the contents of each file to a set of paths with filename concatenated.

For me, instead of given a list of paths, I was given a Directory and asked to return List of List of duplicate files for all under it. 
I chose to represent a Directory like:

class Directory{
     List<Directory> subDirectories;
     List<File> files;
}
Given a directory, you are asked how you can find duplicate files given very large files. 
The idea here is that you cannot store contents in memory, so you need to store the file contents in disk. 
So you can hash each file content and store the hash as a metadata field for each file. 
Then as you perform your search, store the hash instead the file's contents in memory. 
So the idea is you can do a DFS through the root directory and create a HashMap<String, Set<String>> mapping each hash to the Set of filepaths + filenames 
that correspond to that hash's content.

(Note: You can choose BFS / DFS to traverse the Path. I chose DFS as it is more memory efficient and quicker to code up.)

Follow Up: This is great, but it requires you to compute the hash for every single file once, which can be expensive for large files. 
Is there anyway you can avoid computing the hash for a file?

One approach is to also maintain a metadata field for each file's size on disk. Then you can take a 2 pass approach:

DFS to map each size to a set of paths that have that size
For each size, if there are more than 2 files there, compute hash of every file, if any files with the same size have the same hash, then they are identical files.
This way, you only compute hashes if you have multiple files with the same size. So when you do a DFS, you can create a HashMap<Integer, Set<String>>, 
mapping each file's size to the list of file paths that have that size. Loop through each String in each set, get its hash, check if it exists in your set, 
if so, add it to your List<String> res otherwise add it into the set. In between each key (switching file sizes), you can add your res to your List<List<String>>.

*/
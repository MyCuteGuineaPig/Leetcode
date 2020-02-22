/*

733. Flood Fill

Time	    Space	Difficulty
O(m * n)	O(m * n)	Easy
不需要visited unorderdmap 来记录到过的点


An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input: 
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: 
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected 
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].


*/

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor, int prev = numeric_limits<int>::min()) {
        if(image.empty() || image[0].empty() || sr < 0 || sc < 0 
           || sr >= image.size() || sc>=image[0].size()
           || prev !=numeric_limits<int>::min() && image[sr][sc]!= prev || image[sr][sc] == newColor)
            return image;
        prev = image[sr][sc];
        image[sr][sc] = newColor;
        vector<int>dir = {-1,0,1,0};
        for(int i = 0; i<4; i++){
            int x = sr + dir[i];
            int y = sc + dir[(i+1)%4];
            floodFill(image, x, y, newColor, prev);
        }
        return image;
    }
};



class Solution {
public:
    int n, m;
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        n = image.size(); m = image[0].size();
        if(image[sr][sc]!=newColor)
            dfs(image,sr,sc,newColor, image[sr][sc]);
        return image;
    }
    
    void dfs(vector<vector<int>>& image, int sr, int sc, const int & newColor,int startColor) {
        //cout<<"sr "<<sr<<" sc "<<sc<<" startcolor "<<startColor<<endl;
        if(sr<0 || sc<0 || sr>= n || sc>=m || image[sr][sc]!=startColor ) return;
        image[sr][sc] = newColor;
        dfs(image,sr-1,sc,newColor,startColor);
        dfs(image,sr,sc-1,newColor,startColor);
        dfs(image,sr+1,sc,newColor,startColor);
        dfs(image,sr,sc+1,newColor,startColor);
    }
};

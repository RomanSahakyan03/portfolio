// Problem: Zigzag Conversion
// Difficulty: Medium
// Description:
// Given a string s and a number of rows, convert the string "s" into a zigzag pattern and return the result as a string.
// The zigzag pattern is created by writing the characters of "s" in a diagonal line on a given number of rows.
//
// Example:
// Input: s = "PAYPALISHIRING", numRows = 3
// Output: "PAHNAPLSIIGYIR"
//
// Note:
// 1 <= s.length <= 1000
// s consists of English letters (lower-case and upper-case), ',' and '.'.
// 1 <= numRows <= 1000

#include <string>
#include <vector>

class Solution {
public:
    std::string convert(std::string s, int numRows) {

        if(numRows == 1) return s;
        
        std::vector<std::vector<char>> zigzag(numRows, std::vector<char>(s.size()/2 + 1));
        std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(s.size()/2 + 1 , false));

        int i{}, j{}, k{};
        bool approached_bottom = false;

        while(k != s.size()){

            if(i == zigzag.size() - 1) approached_bottom = true;
            if(i == 0) approached_bottom = false;

            zigzag[i][j] = s[k];
            visited[i][j] = true;

            approached_bottom ? --i, ++j : ++i;
            
            ++k;
        }

        std::string res;
        for(int i = 0; i < zigzag.size(); ++i){
            for(int j = 0; j < zigzag[i].size(); ++j){
                if(visited[i][j]){
                    res.push_back(zigzag[i][j]);
                }
            }
        }
        return res;
    }
};
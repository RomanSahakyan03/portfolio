//Problem: Longest Substring Without Repeating Characters
//Difficulty: Medium
//Description:
//Given a string s, find the length of the longest substring without repeating characters.
//
//Examples:
//Input: s = "abcabcbb"
//Output: 3
//Explanation: The answer is "abc", with the length of 3.
//
//Input: s = "bbbbb"
//Output: 1
//Explanation: The answer is "b", with the length of 1.
//
//Input: s = "pwwkew"
//Output: 3
//Explanation: The answer is "wke", with the length of 3.
//Note: Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

#include <string>
#include <deque>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        
        std::deque<char> lenght;
        int res{}, sup_index{};

        for(const auto &ch: s){

            lenght.push_back(ch);
            
            for(int i = 0; i < lenght.size(); ++i){
                if( i !=  lenght.size() - 1 && lenght[i] == lenght.back()){
                    lenght.erase(lenght.begin(), lenght.begin() + i + 1);
                }
            }
            

            res = std::max(res, (int)lenght.size());
        }
        return res;

    }
};
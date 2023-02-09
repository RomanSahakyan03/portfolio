// Problem: Container With Most Water
// Difficulty: Medium
// Description: Given an integer array height of length n,
// find two lines that form a container with the x-axis and contain the most water.
// The container must be a rectangle with sides parallel to the x-axis and y-axis.
// Return the maximum amount of water that can be stored.
//
// Examples: Input: height = [1,8,6,2,5,4,8,3,7], Output: 49. Input: height = [1,1], Output: 1.
//
// Constraints: 2 <= n <= 105, 0 <= height[i] <= 104.

#include <vector>

class Solution {
public:
    int maxArea(std::vector<int>& height){
        int max{};
        int l{}, r{(int)(height.size() - 1)};

        while(l < r){
            int area = (r - l) * std::min(height[r], height[l]);
            max = std::max(max, area);
            if(height[l] < height[r]) ++l;
            else --r;
        }
        return max;
    }
};
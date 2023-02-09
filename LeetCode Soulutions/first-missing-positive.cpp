// Problem: First Missing Positive
// Difficulty: Hard
// Description:
// Given an unsorted integer array nums, return the smallest missing positive integer.
// The algorithm must run in O(n) time and use constant extra space.
//
// Example:
// Input: nums = [1,2,0]
// Output: 3
// Explanation: The numbers in the range [1,2] are all in the array.
//
// Constraints:
// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1

#include <vector>

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        int res{1};
        std::set<int> sorted;

        for(const auto& x: nums){
            if(x > 0)
                sorted.insert(x);
        }

        for(const auto &y: sorted){
            if(y != res){
                break;
            }
            ++res;
        }

        return res;
    }
};
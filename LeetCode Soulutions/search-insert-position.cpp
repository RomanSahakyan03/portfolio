// Problem: Search Insert Position
// Difficulty: Easy
// Description:
// Given a sorted array of distinct integers and a target value, return the index if the target is found.
// If not, return the index where it would be if it were inserted in order.
// You must write an algorithm with O(log n) runtime complexity.
// Examples:
// Input: nums = [1,3,5,6], target = 5
// Output: 2
//
// Input: nums = [1,3,5,6], target = 2
// Output: 1
//
// Input: nums = [1,3,5,6], target = 7
// Output: 4
//Constraints:
// 1 <= nums.length <= 104
// -104 <= nums[i] <= 104
// nums contains distinct values sorted in ascending order.
// -104 <= target <= 104

#include <vector>

class Solution {
public:

    int bsearch(std::vector<int>& arr, int begin, int end, int target){
        
        int mid = (end + begin)/2;

        if(arr[mid] == target) return mid;

        if(end - begin == 1){
            if(target < arr[begin]) return begin;
            else return end;
        };

        if(arr[mid] > target) return bsearch(arr, begin, mid, target);

        if(arr[mid] < target) return bsearch(arr, mid, end, target);

        return -1;
    }

    int searchInsert(std::vector<int>& nums, int target) {
        return bsearch(nums, 0, nums.size(), target);
    }
};
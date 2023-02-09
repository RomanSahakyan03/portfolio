// Problem: Search a 2D Matrix
// Difficulty: Medium
// Description:
// Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
// Example:
// Input: nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
// Explanation:
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]

#include <vector>

class Solution {
public:

    void reverseArray(int i, int j, std::vector<int> &arr){
	    while(i<j){	            
	        std::swap(arr[i], arr[j]);
	        i++;
	        j--;
	    }
    }

    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        reverseArray(0 ,  nums.size()-1 ,  nums);
	    reverseArray(0 ,  k-1 ,  nums);
	    reverseArray(k,  nums.size()-1 ,  nums);
    }
};
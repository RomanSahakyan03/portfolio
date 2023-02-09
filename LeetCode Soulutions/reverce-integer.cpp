// Problem: Reverse Integer
// Difficulty: Medium
// Description:
// Given a signed 32-bit integer x, return x with its digits reversed.
// If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
//
// Example:
// Input: x = 123
// Output: 321
//
// Input: x = -123
// Output: -321
//
// Input: x = 120
// Output: 21
//
// Note:
// Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
// Constraints: -231 <= x <= 231 - 1

#include <vector>

class Solution {
public:
    int reverse(int x) {

        std::vector<short> storage;
        while(x){
            storage.push_back(x%10);
            x /= 10;
        }

        if(storage.size() > 10){
            return 0;
        }

        long reversed{};
        long mul = 1;

        while(!storage.empty()){
            reversed += storage.back() * mul;

            if(reversed >= INT_MAX || reversed <= INT_MIN) return 0;

            storage.pop_back();
            mul *= 10;
        }

        

        return (int)reversed;
    }
};
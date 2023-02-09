// Problem: String to Integer (atoi)
// Difficulty: Medium
// Description:
// Implement a function that converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).
// The function should follow the steps specified in the problem statement:
// ignore leading whitespace, read in a sign, read in digits, convert to integer,
// clamp to 32-bit range, and return the final result.
//
// Example:
// Input: s = "42"
// Output: 42
//
// Input: s = " -42"
// Output: -42
//
// Input: s = "4193 with words"
// Output: 4193
//
// Note:
// Only the space character ' ' is considered a whitespace character. The input string may contain other characters but they will be ignored.
// Constraints: 0 <= s.length <= 200, s consists of English letters, digits, ' ', '+', '-', and '.'.

#include <string>

class Solution {
public:
    int myAtoi(std::string s) {
        int i = 0, sign = 1;
        long long res = 0;

        while (s[i] == ' ') {
            i++;
        }

        if (s[i] == '+' || s[i] == '-') {
            sign = (s[i++] == '-') ? -1 : 1;
        }

        while (s[i] >= '0' && s[i] <= '9') {
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && s[i] - '0' > INT_MAX % 10)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            res = res * 10 + s[i++] - '0';
        }

        if (res < INT_MIN) return INT_MIN;
        if (res > INT_MAX) return INT_MAX;
        return (int)res * sign;
    }


};
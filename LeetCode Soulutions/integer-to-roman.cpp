// Problem: Integer to Roman
// Difficulty: Medium
// Description: Given an integer, convert it to a Roman numeral.
// The Roman numerals are represented by seven symbols: 
// I, V, X, L, C, D and M, with values 1, 5, 10, 50, 100, 500, 1000 respectively.
// There are 6 instances where subtraction is used, such as IV (1 before 5) and IX (1 before 10).
// The conversion should be done following the rules of Roman numeral representation and should be largest to smallest from left to right,
// except for the subtraction instances.
// Input: num = 1994
// Output: "MCMXCIV"
// Constraints: 1 <= num <= 3999

#include <vector>
#include <string>

class Solution {
public:
    string intToRoman(int num) {
        std::vector<std::string> ones = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
        std::vector<std::string> tens = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
        std::vector<std::string> hrns = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
        std::vector<std::string> ths = {"","M","MM","MMM"};
        
        return ths[num/1000] + hrns[(num%1000)/100] + tens[(num%100)/10] + ones[num%10];
    }
};
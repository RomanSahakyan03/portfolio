
// Problem: Add Two Numbers
// Difficulty: Medium
// Description:
// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each of their nodes contains a single digit.
// Add the two numbers and return the sum as a linked list.
//
// Example:
// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
// Explanation: 342 + 465 = 807.
//
// Note:
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.



#include <stack>
#include <vector>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = nullptr;
        ListNode* others = nullptr;
        int flag{};
        std::stack<int, std::vector<int> > nums;
        while(l1 && l2){

            nums.push((l1->val + l2->val + flag)%10 );

            flag = (l1->val + l2->val + flag)/10;

            l1 = l1->next;
            l2 = l2->next;
        }

        l1 ? others = l1 : others = l2;

        while(others){
            nums.push((others->val + flag)%10);

            flag = (others->val + flag)/10;
            others = others->next;
        }

        if (flag){
            nums.push(flag);
        }

        while(!nums.empty()){
            res = new ListNode(nums.top(), res);
            nums.pop();
        }
        return res;
    }
};
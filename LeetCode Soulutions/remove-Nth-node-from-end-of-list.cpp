// Problem: Remove Nth Node From End of List
// Difficulty: Medium
// Description: Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
// Constraints: The number of nodes in the list is sz. 1 <= sz <= 30, 0 <= Node.val <= 100, 1 <= n <= sz.



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


class Solution {
public:

    ListNode* removeNthFromEnd(ListNode* head, int n) {

        ListNode *fast = head, *slow = head;

        for (int i = 0; i < n; i++) fast = fast->next;

        if (!fast) return head->next;

        while (fast->next) fast = fast->next, slow = slow->next;

        slow->next = slow->next->next;
        
        return head;
        }
};
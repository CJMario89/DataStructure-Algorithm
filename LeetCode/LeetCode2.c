/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* MergeL(struct ListNode* l1, struct ListNode* l2){
    int num1 = 0;
    int num2 = 0;
    int num = 0;
    int carry = 0;
    struct ListNode* LCur = (struct ListNode*)malloc(sizeof(struct ListNode));
    LCur->val = 0;
    LCur->next = NULL;
    struct ListNode* L;
    struct ListNode* head1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* head2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    head1->next = l1;
    head2->next = l2;
    struct ListNode* cur1 = head1;
    struct ListNode* cur2 = head2;
    int i = 0;
    while(cur1->next != NULL || cur2->next != NULL){
        num1 = 0;
        num2 = 0;
        if(cur1->next != NULL){
            num1 = cur1->next->val;
            cur1 = cur1->next;
        }
        if(cur2->next != NULL){
            num2 = cur2->next->val;
            cur2 = cur2->next;
        }
        num = num1 + num2 + carry;
        carry = 0;
        if(num >= 10){
            carry = 1;
            num %= 10;
        }
        LCur->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        LCur->next->val = num;
        LCur->next->next = NULL;
        LCur = LCur->next;
        if(i == 0){
            L = LCur;
        }
        i++;
    }
    if(carry == 1){
        LCur->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        LCur->next->next = NULL;
        LCur->next->val = 1;
    }
    return L;
}



struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
     return MergeL(l1, l2);
}

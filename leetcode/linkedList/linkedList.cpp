#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <list>
#include <unordered_set>
#include <map>
#include <cmath>

using namespace std;

#define MAXN 10
#define INT_MAX 0x7fffffff
#define INT_MIN 0x80000000

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

//合并多个链表
class Solution1 {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode *head = lists[0];
        if (lists.size() == 0) return NULL;
        if (lists.size() == 1) return lists[0];
        for (int i = 1; i < lists.size(); i++) {
            head = merge2Lists(head, lists[i]);
        }
        return head;
    }

    ListNode *merge2Lists(ListNode *l1, ListNode *l2) {
        ListNode *list = new ListNode(-1);
        ListNode *head = list;
        while (l1 && l2) {
            if (l1->val == l2->val) {
                list->next = new ListNode(l1->val);
                list = list->next;
                list->next = new ListNode(l2->val);
                list = list->next;
                l1 = l1->next;
                l2 = l2->next;
            } else if (l1->val > l2->val) {
                list->next = new ListNode(l2->val);
                list = list->next;
                l2 = l2->next;
            } else {
                list->next = new ListNode(l1->val);
                list = list->next;
                l1 = l1->next;
            }
        }
        if (l1) {
            list->next = l1;
        }
        if (l2) {
            list->next = l2;
        }
        return head->next;
    }

    void test() {
        ListNode *list1 = new ListNode(1);
        ListNode *list2 = new ListNode(2);
        ListNode *list3 = new ListNode(3);
        ListNode *list4 = new ListNode(4);
        vector<ListNode *> lists;
        lists.push_back(list1);
        lists.push_back(list2);
        lists.push_back(list3);
        lists.push_back(list4);
        cout << mergeKLists(lists)->val;
    }
};

int main() {
    Solution1 solution1 = Solution1();
    solution1.test();
    return 0;
}

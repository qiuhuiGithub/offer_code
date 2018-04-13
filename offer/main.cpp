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

/**
 * 1.尽量使用迭代器代替指针
 * 2.简单函数推荐使用内联函数
 */

template<class T>
int ARRAY_SIZE(T &x) {
    return sizeof(x) / sizeof(x[0]);
}

inline int64_t NumberConvert(double x) { return static_cast<int64_t>(x * 10000); }

inline int max(int number1, int number2) { return number1 > number2 ? number1 : number2; }

inline int min(int number1, int number2) { return number1 < number2 ? number1 : number2; }

inline int max3(int number1, int number2, int number3) {
    return number1 > (number2 > number3 ? number2 : number3) ? number1 : (number2 > number3 ? number2 : number3);
}

inline int min3(int number1, int number2, int number3) {
    return number1 < (number2 < number3 ? number2 : number3) ? number1 : (number2 < number3 ? number2 : number3);
}

//二叉树非递归遍历
class BinaryTree {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    //先序遍历
    void preOrder(TreeNode *root) {
        if (root == NULL)
            return;
        stack<TreeNode *> stack1;
        TreeNode *node = root;
        while (node != NULL || !stack1.empty()) {
            while (node != NULL) {
                cout << node->val << " ";
                stack1.push(node);
                node = node->left;
            }
            node = stack1.top();
            stack1.pop();
            node = node->right;
        }
    }

    //中序遍历
    void inOrder(TreeNode *root) {
        if (root == NULL)
            return;
        stack<TreeNode *> stack1;
        TreeNode *node = root;
        while (node != NULL || !stack1.empty()) {
            while (node != NULL) {
                stack1.push(node);
                node = node->left;
            }
            node = stack1.top();
            cout << node->val << " ";
            stack1.pop();
            node = node->right;
        }
    }


    //后序遍历
    void postOrder(TreeNode *root) {
        if (root == NULL)
            return;
        stack<TreeNode *> stack1;
        stack<TreeNode *> stack2;
        TreeNode *node = root;
        stack1.push(node);
        while (!stack1.empty()) {
            node = stack1.top();
            stack1.pop();
            if (node->left != NULL) {
                stack1.push(node->left);
            }
            if (node->right != NULL) {
                stack1.push(node->right);
            }
            stack2.push(node);
        }
        while (!stack2.empty()) {
            cout << stack2.top()->val << " ";
            stack2.pop();
        }
    }

    void levelOrder(TreeNode *root) {
        if (root == NULL)
            return;
        TreeNode *node = root;
        queue<TreeNode *> queue1;
        queue1.push(node);
        while (!queue1.empty()) {
            node = queue1.front();
            queue1.pop();
            cout << node->val << " ";
            if (node->left)
                queue1.push(node->left);
            if (node->right)
                queue1.push(node->right);
        }
    }

    void test() {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        cout << "preorder:";
        preOrder(root);
        cout << "inorder:";
        inOrder(root);
        cout << "postOrder:";
        postOrder(root);
        cout << "levelOrder";
        levelOrder(root);
    }
};

//二维数组查找
class Solution1 {
public:
    bool Find(vector<vector<int>> array, int target) {
        int row = array.size();
        if (row == 0)
            return false;
        int column = array[0].size();
        int i = 0, j = column - 1;
        while (i < row && j >= 0) {
            if (array[i][j] == target)
                return true;
            else if (array[i][j] > target) {
                j--;
            } else
                i++;
        }
        return false;
    }

    void test() {
        vector<vector<int>> array1{{1,  2,  3,  4,  5},
                                   {6,  7,  8,  9,  10},
                                   {11, 12, 13, 14, 15},
                                   {16, 17, 18, 19, 20}};

        vector<int> target{1, 2, 3, 10, 0, -1, 32, 34, 20, 16, 15, 6};
        for (int i = 0; i != target.size(); i++) {
            cout << "target " << target[i] << boolalpha << "    std:" << (1 <= target[i] && target[i] <= 20) << "  res:"
                 << Find(array1, target[i]) << endl;
        }
    }
};

//给定一个字符串，替换空白符
class Solution2 {
public:
    void replaceSpace(char *str, int length) {
        if (str == NULL || length <= 0)
            return;
        int originLength = 0;
        int numOfBlank = 0;
        int i = 0;
        while (str[i] != '\0') {
            originLength++;
            if (str[i] == ' ')
                numOfBlank++;
            i++;
        }
        int newLength = originLength + numOfBlank * 2;
        if (newLength > length)
            return;
        int indexOfOrigin = originLength;
        int indexOfNew = newLength;
        while (indexOfOrigin >= 0 && indexOfNew > indexOfOrigin) {
            if (str[indexOfOrigin] == ' ') {
                str[indexOfNew--] = '0';
                str[indexOfNew--] = '2';
                str[indexOfNew--] = '%';
            } else {
                str[indexOfNew--] = str[indexOfOrigin];
            }
            indexOfOrigin--;
        }
    }

    void test() {
        char *string1 = "we are happy";
        char buffer[256] = {'\0'};
        strcpy(buffer, string1);
        replaceSpace(buffer, 256);
        cout << "new String:" << buffer << endl;
    }
};


//从尾到头打印链表
class Solution3 {
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) {
            val = x;
            next = NULL;
        }
    };

public:
    vector<int> dev;

    vector<int> printListFromTailToHead(ListNode *head) {
        if (head != NULL) {
            if (head->next != NULL) {
                dev = printListFromTailToHead(head->next);
            }
            dev.push_back(head->val);
        }
        return dev;

    }

    void test() {
        ListNode *p;
        p = new ListNode(1);
        p->next = new ListNode(2);
        p->next->next = new ListNode(3);
        vector<int> vector1 = printListFromTailToHead(p);
        display(vector1);
    }

    void display(vector<int> vector1) {
        vector<int>::iterator it = vector1.begin();
        for (; it != vector1.end(); it++) {
            cout << *it << " ";
        }
    }
};

//给定一棵二叉树的前序和中序遍历结果，建树。
class Solution4 {
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) {
            val = x;
            left = NULL;
            right = NULL;
        }
    };

public:
    TreeNode *Construct(int *preorder, int *inorder, int length) {
        if (preorder == NULL || inorder == NULL || length <= 0)
            return NULL;
        return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
    }

    TreeNode *ConstructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder) {
        //前序遍历第一个数字为根节点的值
        int rootValue = startPreorder[0];
        TreeNode *root = new TreeNode(rootValue);
        root->left = root->right = NULL;
        if (startPreorder == endPreorder) {
            if (startInorder == endInorder && *startPreorder == *startInorder)
                return root;
            else
                throw exception();
        }

        int *rootInorder = startInorder;
        while (rootInorder <= endInorder && *rootInorder != rootValue)
            ++rootInorder;
        if (rootInorder == endInorder && *rootInorder != rootValue)
            throw exception();
        int leftLength = rootInorder - startInorder;
        int *leftPreorderEnd = startPreorder + leftLength;
        if (leftLength > 0) {
            root->left = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
        }
        if (leftLength < endPreorder - startPreorder) {
            root->right = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
        }
        return root;
    }

    void test() {
        int preorder[8] = {1, 2, 4, 7, 3, 5, 6, 8};
        int inorder[8] = {4, 7, 2, 1, 5, 3, 8, 6};
        int length = ARRAY_SIZE(preorder);
        TreeNode *root = Construct(preorder, inorder, length);
        inOrder(root);
    }

    //验证结果
    void inOrder(TreeNode *root) {
        if (root == NULL)
            return;
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
};


//两个栈模拟队列
class Solution5 {
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                int val = stack1.top();
                stack2.push(val);
                stack1.pop();
            }
        }
        int res = stack2.top();
        stack2.pop();
        return res;
    }

    void test() {
        push(1);
        push(2);
        push(3);
        int res = pop();
        cout << res;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

//旋转数组的最小值
class Solution6 {
public:
    int Min(vector<int> number, int length) {
        if (number.empty() || length <= 0)
            throw exception();
        int start = 0;
        int end = length - 1;
        int mid;
        while (number[start] >= number[end]) {
            if (end - start == 1) {
                return number[end];
            }
            mid = start + (end - start) / 2;
            if (number[start] == number[end] && number[mid] == number[end]) {
                return MidInOrder(number, start, end);
            }
            if (number[mid] >= number[start]) {
                start = mid;
            } else if (number[mid] <= number[end]) {
                end = mid;
            }
        }
        return number[mid];
    }

    int MidInOrder(vector<int> number, int start, int end) {
        int result = number[start];
        for (int i = start + 1; i < end; i++) {
            if (number[i] < result) {
                result = number[i];
            }
        }
        return result;
    }

    void test() {
        vector<int> number{3, 4, 5, 1, 2};
        int length = ARRAY_SIZE(number);
        cout << Min(number, length) << endl;
    }
};

//青蛙跳台阶,动态规划
class Solution7 {
public:
    int jumpFloorII(int number) {
        if (number == 0)
            return 0;
        int dp[number + 1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= number; i++) {
            dp[i] = 0;
            for (int j = 0; j < i; j++) {
                dp[i] += dp[j];
            }
        }
        return dp[number];
    }

    void test() {
        cout << jumpFloorII(10) << endl;
    }
};

//计算平方
class Solution8 {
public:
    bool g_InvalidInput = false;

    double Power(double base, int exponent) {
        g_InvalidInput = false;
        if (equal(base, 0.0) && exponent < 0) {
            g_InvalidInput = true;
            return 0.0;
        }

        unsigned int absExponent = (unsigned int) (exponent);
        if (exponent < 0)
            absExponent = (unsigned int) (-exponent);
        double result = PowerWithUnsignedExponent(base, absExponent);
        if (exponent < 0)
            result = 1.0 / result;
        return result;
    }

    double PowerWithUnsignedExponent(double base, int absExponent) {
        double result = 1;
        for (int i = 0; i < absExponent; i++) {
            result *= base;
        }
        return result;
    }

    bool equal(double num1, double num2) {
        if (fabs(num1 - num2) < 0.000001)
            return true;
        else
            return false;

    }

    void test() {
        cout << Power(2.3, 4) << endl;
    }
};


//链表删除节点
class Solution9 {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    void DeleteNode(ListNode *pListHead, ListNode *pToBeDeleted) {
        if (!pListHead || !pToBeDeleted)
            return;
        //要删除的节点不是尾节点
        if (pToBeDeleted->next != NULL) {
            ListNode *nextNode = pToBeDeleted->next;
            pToBeDeleted->val = nextNode->val;
            pToBeDeleted->next = nextNode->next;

            delete nextNode;
        }//删除头结点
        else if (pToBeDeleted == pListHead) {
            delete pToBeDeleted;
            pListHead = NULL;
        } else {
            ListNode *pNode = pListHead;
            while (pNode->next != pToBeDeleted) {
                pNode = pNode->next;
            }
            pNode->next = NULL;
            delete pToBeDeleted;
        }
    }

    void test() {
        ListNode *pHead = new ListNode(1);
        pHead->next = new ListNode(2);
        ListNode *pToBeDelete = new ListNode(3);
        pHead->next->next = pToBeDelete;
        pToBeDelete->next = new ListNode(4);
        DeleteNode(pHead, pToBeDelete->next);
        while (pHead != NULL) {
            cout << pHead->val << " ";
            pHead = pHead->next;
        }
    }
};

//给定数组，调整顺序使得奇数排在偶数后面
class Solution10 {
public:
    void ReorderEven(int *pData, unsigned int length) {
        int *pBegin = pData;
        int *pEnd = pData + length - 1;
        while (pBegin < pEnd) {
            while (pBegin < pEnd && *pBegin % 2 != 0)
                pBegin++;
            while (pBegin < pEnd && *pEnd % 2 == 0)
                pEnd--;
            if (pBegin < pEnd) {
                int temp = *pBegin;
                *pBegin = *pEnd;
                *pEnd = temp;
            }
        }
    }

    void test() {
        int pData[5] = {1, 2, 3, 4, 5};
        ReorderEven(pData, ARRAY_SIZE(pData));
        for (int i = 0; i < ARRAY_SIZE(pData); i++) {
            cout << pData[i] << " ";
        }
    }

};

//链表找倒数第K个节点，快慢指针。
class Solution11 {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    ListNode *FindKthToTail(ListNode *pHead, int k) {
        ListNode *first = pHead;
        ListNode *second = pHead;
        for (int i = 0; i < k; i++) {
            first = first->next;
        }
        while (first != NULL) {
            first = first->next;
            second = second->next;
        }
        return second;

    }

    void test() {
        ListNode *pHead = new ListNode(1);
        pHead->next = new ListNode(2);
        pHead->next->next = new ListNode(3);
        cout << FindKthToTail(pHead, 2)->val << endl;
    }

};


//反转链表
class Solution12 {
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

public:
    ListNode *ReverseList(ListNode *pHead) {
        ListNode *pReversedHead = NULL;
        ListNode *pNode = pHead;
        ListNode *pPrev = NULL;
        while (pNode != NULL) {
            ListNode *pNext = pNode->next;
            if (pNext == NULL) {
                pReversedHead = pNode;
            }
            pNode->next = pPrev;
            pPrev = pNode;
            pNode = pNext;
        }
        return pReversedHead;
    }

    void test() {
        ListNode *pHead = new ListNode(1);
        pHead->next = new ListNode(2);
        pHead->next->next = new ListNode(3);
        ListNode *list = ReverseList(pHead);
        while (list != NULL) {
            cout << list->val << " ";
            list = list->next;
        }
    }
};

//大数加法
class Solution13 {
public:
    void Add(char *s1, char *s2) {
        int num1[MAXN], num2[MAXN];
        memset(num1, 0, sizeof(num1));
        memset(num2, 0, sizeof(num2));
        int i, j;
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        for (i = len1 - 1, j = 0; i >= 0; i--) {
            num1[j++] = s1[i] - '0';
        }
        for (i = len2 - 1, j = 0; i >= 0; i--) {
            num2[j++] = s2[i] - '0';
        }
        for (i = 0; i < MAXN; i++) {
            num1[i] += num2[i];
            if (num1[i] > 9) {
                num1[i] = num1[i] - 10;
                num1[i + 1] += 1;
            }
        }
        for (i = MAXN - 1; i >= 0; i--) {
            if (num1[i])
                break;
        }
        for (j = i; j >= 0; j--) {
            cout << num1[j];
        }
    }

    void test() {
        char s1[5] = "12";
        char s2[5] = "89";
        Add(s1, s2);
    }
};

//链表合并
class Solution14 {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    ListNode *Merge(ListNode *first, ListNode *second) {
        if (first == NULL)
            return second;
        if (second == NULL)
            return first;
        ListNode *newList = NULL;
        if (first->val < second->val) {
            newList = first;
            newList->next = Merge(first->next, second);
        } else {
            newList = second;
            newList->next = Merge(first, second->next);
        }
        return newList;
    }

    void test() {
        ListNode *first = new ListNode(1);
        first->next = new ListNode(2);
        first->next->next = new ListNode(3);
        ListNode *second = new ListNode(2);
        second->next = new ListNode(4);
        ListNode *newList = Merge(first, second);
        while (newList != NULL) {
            cout << newList->val;
            newList = newList->next;
        }
    }
};

//判断子树A是否包含子树B
class Solution15 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    bool HasSubTree(BinaryTreeNode *a, BinaryTreeNode *b) {
        bool flag = false;
        if (a != NULL && b != NULL) {
            if (a->val == b->val)
                flag = DoesTree1HasTree2(a, b);
            if (!flag)
                flag = HasSubTree(a->left, b);
            if (!flag)
                flag = HasSubTree(a->right, b);
        }
        return flag;
    }

    bool DoesTree1HasTree2(BinaryTreeNode *a, BinaryTreeNode *b) {
        if (b == NULL)
            return true;
        if (a == NULL)
            return false;
        if (a->val != b->val)
            return false;
        return DoesTree1HasTree2(a->left, b->left) && DoesTree1HasTree2(a->right, b->right);
    }

    void test() {
        BinaryTreeNode *a = new BinaryTreeNode(1);
        a->left = new BinaryTreeNode(2);
        a->right = new BinaryTreeNode(3);
        BinaryTreeNode *b = new BinaryTreeNode(1);
        b->left = new BinaryTreeNode(2);
        bool result = HasSubTree(a, b);
        cout << "flag:" << result;
    }

};

//二叉树的镜像
class Solution16 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void Mirror(BinaryTreeNode *tree) {
        if (tree == NULL)
            return;
        if (tree->left == NULL && tree->right == NULL)
            return;
        BinaryTreeNode *temp = tree->left;
        tree->left = tree->right;
        tree->right = temp;
        if (tree->left)
            Mirror(tree->left);
        if (tree->right)
            Mirror(tree->right);
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(1);
        root->left = new BinaryTreeNode(2);
        root->right = new BinaryTreeNode(3);
        Mirror(root);
        cout << root->val << "," << root->left->val << "," << root->right->val;
    }
};

//环形打印数字
class Solution17 {
public:
    void printMatrix(int numbers[][3], int columns, int rows) {
        if (numbers == NULL || columns <= 0 || rows <= 0)
            return;
        int start = 0;
        while (columns > start * 2 && rows > start * 2) {
            printMatrixInCicle(numbers, columns, rows, start);
            start++;
        }
    }

    void printMatrixInCicle(int numbers[3][3], int columns, int rows, int start) {
        int endX = columns - 1 - start;
        int endY = rows - 1 - start;
        for (int i = start; i <= endX; i++) {
            cout << numbers[start][i];
        }
        if (start < endY) {
            for (int i = start + 1; i <= endY; i++) {
                cout << numbers[i][endX];
            }
        }
        if (start < endX && start < endY) {
            for (int i = endX - 1; i >= start; i--) {
                cout << numbers[endY][i];
            }
        }
        if (start < endX && start < endY - 1) {
            for (int i = endY - 1; i >= start + 1; i--) {
                cout << numbers[i][start];
            }
        }
    }

    void test() {
        int numbers[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        printMatrix(numbers, 3, 3);
    }
};

//找到二叉树中和为某一特定值的路径
class Solution18 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void FindPath(BinaryTreeNode *root, int expectedSum) {
        if (root == NULL)
            return;
        vector<int> path;
        int currentSum = 0;
        FindPath(root, expectedSum, path, currentSum);
    }

    void FindPath(BinaryTreeNode *root, int expectSum, vector<int> &path, int currentSum) {
        currentSum += root->val;
        path.push_back(root->val);
        bool isLeaf = (root->left == NULL) && (root->right == NULL);
        if (currentSum == expectSum && isLeaf) {
            vector<int>::iterator iter = path.begin();
            for (; iter != path.end(); iter++) {
                cout << *iter << "\t";
            }
            cout << endl;
        }
        if (root->left != NULL)
            FindPath(root->left, expectSum, path, currentSum);
        if (root->right != NULL)
            FindPath(root->right, expectSum, path, currentSum);
        path.pop_back();
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(10);
        root->left = new BinaryTreeNode(5);
        root->right = new BinaryTreeNode(12);
        root->left->left = new BinaryTreeNode(4);
        root->left->right = new BinaryTreeNode(7);
        FindPath(root, 22);
    }
};

//二叉树转双向链表
class Solution19 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    BinaryTreeNode *Convert(BinaryTreeNode *pRootOfTree) {
        BinaryTreeNode *pLastNodeInList = NULL;
        ConvertNode(pRootOfTree, &pLastNodeInList);
        BinaryTreeNode *pHeadNodeOfList = pLastNodeInList;
        while (pHeadNodeOfList != NULL && pHeadNodeOfList->left != NULL) {
            pHeadNodeOfList = pHeadNodeOfList->left;
        }
        return pHeadNodeOfList;
    }

    void ConvertNode(BinaryTreeNode *pNode, BinaryTreeNode **pLastNodeInList) {
        if (pNode == NULL)
            return;
        BinaryTreeNode *pCurrent = pNode;
        if (pCurrent->left != NULL)
            ConvertNode(pCurrent->left, pLastNodeInList);
        pCurrent->left = *pLastNodeInList;
        if (*pLastNodeInList != NULL)
            (*pLastNodeInList)->right = pCurrent;
        *pLastNodeInList = pCurrent;
        if (pCurrent->right != NULL)
            ConvertNode(pCurrent->right, pLastNodeInList);
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(10);
        root->left = new BinaryTreeNode(6);
        root->right = new BinaryTreeNode(14);
        BinaryTreeNode *newRoot = Convert(root);
        cout << newRoot->val << endl;

    }
};

//找超过一半的数(第K个数)
class Solution20 {
public:
//    int findKth(vector<int> &numbers, int k) {
//        int length = numbers.size();
//        int start = 0;
//        int end = length - 1;
//        int index = partition(numbers, length, start, end);
//        while (index != k) {
//            if (index < k) {
//                index = partition(numbers, length, index + 1, end);
//            } else
//                index = partition(numbers, length, start, index - 1);
//        }
//        int result = numbers[index];
//        return result;
//    }

    int MoreThanHalf(int *numbers, int length) {
        int middle = length / 2;
        int start = 0;
        int end = length - 1;
        int index = partition(numbers, length, start, end);
        while (index != middle) {
            if (index < middle) {
                index = partition(numbers, length, index + 1, end);
            } else
                index = partition(numbers, length, start, index - 1);
        }
        int result = numbers[index];
        if (CheckMoreThanHalf(numbers, result)) {
            return result;
        }
        return -1;
    }

    int partition(int *numbers, int length, int start, int end) {
        if (numbers == NULL)
            throw new exception();
        int x = numbers[start];
        int i = start + 1;
        int j = end;
        while (true) {
            while (i <= j && numbers[j] >= x)
                j--;
            if (i > j) break;
            while (i <= j && numbers[i] <= x)
                i++;
            if (i > j) break;
            swap(&numbers[i++], &numbers[j--]);
        }
        swap(&numbers[j], &numbers[start]);
        return j;
    }

    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    int MoreThanHalf2(int *numbers, int length) {
        int result = numbers[0];
        int times = 1;
        for (int i = 1; i < length; i++) {
            if (times == 0) {
                result = numbers[i];
                times = 1;
            } else if (numbers[i] == result) {
                times++;
            } else {
                times--;
            }
        }
        if (CheckMoreThanHalf(numbers, result)) {
            return result;
        }
        return -1;
    }

    bool CheckMoreThanHalf(int *numbers, int target) {
        bool isMoreThanHalf = false;
        int times = 0;
        for (int i = 0; i < 5; i++) {
            if (numbers[i] == target)
                times++;
        }
        if (times * 2 >= 5)
            isMoreThanHalf = true;
        return isMoreThanHalf;
    }

    void test() {
        int numbers[5] = {3, 1, 2, 4, 2};
        int result = MoreThanHalf2(numbers, ARRAY_SIZE(numbers));
        cout << result;
    }
};

//找数组中和最大连续子数组
class Solution21 {
public:
    int FindGreatestSumOfSubArray(int *numbers, int length) {
        if (numbers == NULL || length == 0)
            return -1;
        int curSum = 0;
        int greatSum = INT_MIN;
        for (int i = 0; i < length; i++) {
            if (i == 0 || curSum < 0)
                curSum = numbers[i];
            else
                curSum += numbers[i];
            if (curSum > greatSum)
                greatSum = curSum;
        }
        return greatSum;
    }

    void test() {
        int numbers[8] = {1, -2, 3, 10, -4, 7, 2, -5};
        int greatestSum = FindGreatestSumOfSubArray(numbers, 8);
        printf("%d\n", greatestSum);
    }
};

//丑数
class Solution22 {
public:
    int getUglyNumber(int index) {
        if (index <= 0)
            return 0;
        int *pUglyNumbers = new int[index];
        pUglyNumbers[0] = 1;
        int nextUglyIndex = 1;
        int *pMultiply2 = pUglyNumbers;
        int *pMultiply3 = pUglyNumbers;
        int *pMultiply5 = pUglyNumbers;
        while (nextUglyIndex < index) {
            int min = min3(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
            pUglyNumbers[nextUglyIndex] = min;
            while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
                ++pMultiply2;
            while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
                ++pMultiply3;
            while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
                ++pMultiply5;
            ++nextUglyIndex;
        }
        int ugly = pUglyNumbers[nextUglyIndex - 1];
        delete[] pUglyNumbers;
        return ugly;
    }

    void test() {
        cout << getUglyNumber(1500);
    }
};

//找到第一个只出现一次的字符
class Solution23 {
public:
    char FirstNotRepeatingChar(char *pString) {
        if (pString == NULL)
            return '\0';
        const int tableSize = 256;
        int hashTable[tableSize];
        for (int i = 0; i < tableSize; i++) {
            hashTable[i] = 0;
        }
        char *key = pString;
        while (*key != '\0') {
            hashTable[*key]++;
            key++;
        }
        key = pString;
        while (*key != '\0') {
            if (hashTable[*key] == 1)
                return *key;
            key++;
        }
        return '\0';

    }

    void test() {
        char pString[6] = "abacd";
        cout << FirstNotRepeatingChar(pString);
    }
};

//二叉树的深度和判断二叉树是否平衡
class Solution24 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    int TreeDepth(BinaryTreeNode *pRoot) {
        if (pRoot == NULL)
            return 0;
        int nLeft = TreeDepth(pRoot->left);
        int nRight = TreeDepth(pRoot->right);
        return nLeft > nRight ? (nLeft + 1) : (nRight + 1);
    }

    bool IsBalanced(BinaryTreeNode *pRoot, int *depth) {
        if (pRoot == NULL) {
            *depth = 0;
            return true;
        }
        int left, right;
        if (IsBalanced(pRoot->left, &left) && IsBalanced(pRoot->right, &right)) {
            int diff = left - right;
            if (diff <= 1 && diff >= -1) {
                *depth = 1 + (left > right ? left : right);
                return true;
            }
        }
        return false;
    }

    bool IsBalanced(BinaryTreeNode *pRoot) {
        int depth = 0;
        return IsBalanced(pRoot, &depth);
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(1);
        //cout << TreeDepth(root);
        cout << IsBalanced(root);
    }
};

//数组中只出现一次的数
class Solution25 {
public:
    void FindNumsAppearonce(int data[], int length, int *num1, int *num2) {
        if (data == NULL || length < 2)
            return;
        int resultExclusiveOR = 0;
        for (int i = 0; i < length; i++) {
            resultExclusiveOR ^= data[i];
        }
        int indexOf1 = FindFirstBitIs1(resultExclusiveOR);
        *num1 = *num2 = 0;
        for (int j = 0; j < length; j++) {
            if (IsBit1(data[j], indexOf1))
                *num1 ^= data[j];
            else
                *num2 ^= data[j];
        }
    }

    int FindFirstBitIs1(int num) {
        int indexBit = 0;
        while (((num & 1) == 0) && (indexBit < 8 * sizeof(int))) {
            num = num >> 1;
            indexBit++;
        }
        return indexBit;
    }

    bool IsBit1(int num, unsigned int indexBit) {
        num = num >> indexBit;
        return num & 1;
    }

    void test() {
        int data[6] = {3, 3, 6, 4, 5, 5};
        int num1, num2;
        FindNumsAppearonce(data, 6, &num1, &num2);
        cout << num1 << "," << num2;
    }
};

//约瑟夫环，最后剩下的数
class Solution26 {
public:
    int lastRemaining(unsigned int n, unsigned int m) {
        if (n < 1 || m < 1)
            return -1;
        std::list<int> numbers;
        for (int i = 1; i < n; i++)
            numbers.push_back(i);
        std::list<int>::iterator current = numbers.begin();
        std::list<int>::iterator next;
        while (numbers.size() > 1) {
            for (int i = 1; i < m; i++) {
                current++;
                if (current == numbers.end())
                    current = numbers.begin();
            }
            next = ++current;
            if (next == numbers.end())
                next = numbers.begin();
            --current;
            numbers.erase(current);
            current = next;
        }
        return *(current);
    }

    int lastRemaining2(int n, int m) {
        if (n < 1 || m < 1)
            return -1;
        int last = 0;
        for (int i = 2; i <= n; i++) {
            last = (last + m) % n;
        }
        return last;
    }

    void test() {
        cout << lastRemaining(5, 3);
    }
};

//数字枚举
class Solution27 {
public:
    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void perm(int list[], int k, int m) {
        if (k == m) {
            for (int i = 0; i < m; i++) {
                cout << list[i];
            }
            cout << endl;
        } else {
            for (int i = k; i < m; i++) {
                swap(&list[k], &list[i]);
                perm(list, k + 1, m);
                swap(&list[k], &list[i]);
            }
        }
    }

    void test() {
        int list[] = {1, 2, 3};
        perm(list, 0, 3);
    }
};


//二叉树的最右节点
class Solution28 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    BinaryTreeNode *lastNode(BinaryTreeNode *root) {
        if (root == NULL || root->left == NULL)
            return root;
        int leftDepth = 0;
        int rightDepth = 0;
        BinaryTreeNode *leftNode = root->left;
        while (leftNode != NULL) {
            leftDepth++;
            leftNode = leftNode->left;
        }
        BinaryTreeNode *rightNode = root->right;
        while (rightNode != NULL) {
            rightDepth++;
            rightNode = rightNode->left;
        }
        if (leftDepth > rightDepth)
            return lastNode(root->left);
        else
            return lastNode(root->right);
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(1);
        root->left = new BinaryTreeNode(2);
        root->right = new BinaryTreeNode(3);
        cout << lastNode(root)->val;
    }
};


//环形链表的入口节点
class Solution29 {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    ListNode *EntryNodeOfLoop(ListNode *head) {
        if (head == NULL)
            return NULL;
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != NULL || fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow)
                break;
        }
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    void test() {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        ListNode *temp = head->next->next;
        temp->next = new ListNode(4);
        temp->next->next = head->next;
        cout << EntryNodeOfLoop(head)->val;
    }
};

//数组中重复的数字
class Solution30 {
public:
    int duplicate(int numbers[], int length) {
        if (numbers == NULL || length < 0)
            return -1;
        for (int i = 0; i < length; i++) {
            if (numbers[i] < 0 || numbers[i] > length - 1)
                return -1;
        }
        for (int i = 0; i < length; i++) {
            while (numbers[i] != i) {
                if (numbers[i] == numbers[numbers[i]])
                    return numbers[i];
                else {
                    int temp = numbers[i];
                    numbers[i] = numbers[numbers[i]];
                    numbers[numbers[i]] = temp;
                }
            }
        }
        return -1;
    }

    void test() {
        int numbers[6] = {0, 1, 2, 3, 4, 5};
        cout << duplicate(numbers, 6);
    }
};

//岛屿的数量，连一起的1表示陆地，0表示海洋，找到岛屿数量。DFS和BFS。
class Solution31 {
public:
    int numOflands(char grid[][5], int m, int n) {
        int count = 0;
        if (grid == NULL)
            return 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    DFS(grid, i, j, &count);
                    //BFS(grid, i, j);
                    //count++;
                }
            }
        }
        return count;
    }

    void DFS(char grid[][5], int x, int y, int *p) {
        if (x < 0 || x >= 4 || y < 0 || y >= 5 || grid[x][y] != '1')
            return;
        grid[x][y] = '0';
        *p += 1;
        DFS(grid, x - 1, y, p);
        DFS(grid, x + 1, y, p);
        DFS(grid, x, y - 1, p);
        DFS(grid, x, y + 1, p);
    }

    int dir[4][2] = {{-1, 0},
                     {1,  0},
                     {0,  -1},
                     {0,  1}};

    void BFS(char grid[][5], int x, int y) {
        grid[x][y] = '0';
        queue<vector<int>> queue;
        queue.push({x, y});
        while (!queue.empty()) {
            vector<int> t;
            t = queue.front();
            queue.pop();
            for (int k = 0; k < 4; k++) {
                int i = dir[k][0] + t[0];
                int j = dir[k][1] + t[1];
                if (i < 0 || i > 4 || j < 0 || j > 5 || grid[i][j] == '0')
                    continue;
                grid[i][j] = '0';
                queue.push({i, j});
            }
        }
    }

    void test() {
        char grid[4][5] = {{'1', '1', '1', '1', '0'},
                           {'1', '1', '0', '1', '0'},
                           {'1', '1', '0', '0', '0'},
                           {'0', '0', '0', '0', '0'}};
        cout << numOflands(grid, 4, 5);
    }
};

//字符串的编辑距离
class Solution32 {
public:
    int editDistance(string s1, string s2) {
        int m = s1.length();
        int n = s2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min3(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + 1);
            }
        }
        return dp[m][n];
    }

    void test() {
        string s1 = "abc";
        string s2 = "dd";
        cout << editDistance(s1, s2);
    }
};

//找有多少个1
class Solution33 {
public:
    int numIsHouse(vector<vector<char> > &grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    numIshouseDFS(grid, visited, i, j, &res);
                }
            }
        }
        return res;
    }

    void numIshouseDFS(vector<vector<char> > &grid, vector<vector<bool> > &visited, int x, int y, int *res) {
        if (x < 0 || x >= grid.size()) return;
        if (y < 0 || y >= grid[0].size()) return;
        if (grid[x][y] != '1' || visited[x][y]) return;
        visited[x][y] = true;
        *res += 1;
        numIshouseDFS(grid, visited, x - 1, y, res);
        numIshouseDFS(grid, visited, x + 1, y, res);
        numIshouseDFS(grid, visited, x, y - 1, res);
        numIshouseDFS(grid, visited, x, y + 1, res);
    }

    void test() {
        vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                     {'1', '1', '0', '1', '0'},
                                     {'1', '1', '0', '0', '0'},
                                     {'0', '0', '0', '0', '0'}};
        cout << numIsHouse(grid);

    }
};

//判断二叉树是否对称
class Solution34 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    bool isSymmetrical(BinaryTreeNode *pRoot) {
        if (pRoot == NULL)
            return true;
        return isSymmetrical(pRoot->left, pRoot->right);
    }

    bool isSymmetrical(BinaryTreeNode *left, BinaryTreeNode *right) {
        if (left == NULL && right == NULL)
            return true;
        if (left == NULL || right == NULL)
            return false;
        if (left->val != right->val)
            return false;
        return isSymmetrical(left->left, right->right) && isSymmetrical(left->right, right->left);
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(1);
        root->left = new BinaryTreeNode(2);
        root->right = new BinaryTreeNode(2);
        cout << isSymmetrical(root);
    }
};

//删除链表中重复的节点
class Solution35 {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    ListNode *deleteDuplication(ListNode *pHead) {
        ListNode *head = new ListNode(-1);
        head->next = pHead;
        ListNode *pre = head;
        ListNode *cur = head;
        while (cur != NULL) {
            while (cur->next != NULL && cur->val == cur->next->val) {
                cur = cur->next;
            }
            if (pre->next == cur) {
                pre = pre->next;
            } else {
                pre->next = cur->next;
            }
            cur = cur->next;
        }
        return head->next;
    }

    void test() {
        ListNode *pHead = new ListNode(1);
        pHead->next = new ListNode(2);
        pHead->next->next = new ListNode(3);
        pHead->next->next->next = new ListNode(3);
        //pHead->next->next->next->next = new ListNode(4);
        //pHead->next->next->next->next->next = new ListNode(4);
        //pHead->next->next->next->next->next->next = new ListNode(5);
        pHead = deleteDuplication(pHead);
        while (pHead != NULL) {
            cout << pHead->val;
            pHead = pHead->next;
        }
    }
};

//二叉树的下一个节点
class Solution36 {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode *parent;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    TreeNode *getNext(TreeNode *node) {
        if (node == NULL)
            return NULL;
        TreeNode *pNext = NULL;
        if (node->right != NULL) {
            TreeNode *right = node->right;
            while (right->left != NULL)
                right = right->left;
            pNext = right;
        } else if (node->parent != NULL) {
            TreeNode *parent = node->parent;
            TreeNode *current = node;
            while (current != NULL && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }
            pNext = parent;
        }
        return pNext;
    }

    void test() {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->left->parent = root;
        root->right = new TreeNode(3);
        root->right->parent = root;
        cout << getNext(root->left)->val;
    }
};


//对称二叉树
class Solution37 {
public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void LevelOrder(BinaryTreeNode *root) {
        if (root == NULL)
            return;
        queue<BinaryTreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            vector<BinaryTreeNode *> vec;
            for (int i = 0; i < size; i++) {
                BinaryTreeNode *node = queue.front();
                queue.pop();
                if (node->left)
                    queue.push(node->left);
                if (node->right)
                    queue.push(node->right);
                vec.push_back(node);
            }
            vector<BinaryTreeNode *>::iterator it = vec.begin();
            for (; it != vec.end(); it++) {
                cout << (*it)->val;
            }
            cout << endl;
        }
    }

    void test() {
        BinaryTreeNode *root = new BinaryTreeNode(1);
        root->left = new BinaryTreeNode(2);
        root->right = new BinaryTreeNode(2);
        LevelOrder(root);
    }
};

int main() {
//    BinaryTree binaryTree = BinaryTree();
//    binaryTree.test();
//    Solution1 solution1 = Solution1();
//    solution1.test();
//    Solution2 solution2 = Solution2();
//    solution2.test();
//    Solution3 solution3 = Solution3();
//    solution3.test();
//    Solution4 solution4 = Solution4();
//    solution4.test();
//    Solution5 solution5 = Solution5();
//    solution5.test();
//    Solution6 solution6 = Solution6();
//    solution6.test();
//    Solution7 solution7 = Solution7();
//    solution7.test();
//    Solution8 solution8 = Solution8();
//    solution8.test();
//    Solution9 solution9 = Solution9();
//    solution9.test();
//    Solution10 solution10 = Solution10();
//    solution10.test();
//    Solution11 solution11 = Solution11();
//    solution11.test();
//    Solution12 solution12 = Solution12();
//    solution12.test();
//    Solution13 solution13 = Solution13();
//    solution13.test();
//    Solution14 solution14 = Solution14();
//    solution14.test();
//    Solution15 solution15 = Solution15();
//    solution15.test();
//    Solution17 solution17 = Solution17();
//    solution17.test();
//    Solution18 solution18 = Solution18();
//    solution18.test();
//    Solution19 solution19 = Solution19();
//    solution19.test();
//    Solution20 solution20 = Solution20();
//    solution20.test();
//    Solution21 solution21 = Solution21();
//    solution21.test();
//    Solution22 solution22 = Solution22();
//    solution22.test();
//    Solution23 solution23 = Solution23();
//    solution23.test();
//    Solution24 solution24 = Solution24();
//    solution24.test();
//    Solution25 solution25 = Solution25();
//    solution25.test();
//    Solution26 solution26 = Solution26();
//    solution26.test();
//    Solution27 solution27 = Solution27();
//    solution27.test();
//    Solution28 solution28 = Solution28();
//    solution28.test();
//    Solution29 solution29 = Solution29();
//    solution29.test();
//    Solution30 solution30 = Solution30();
//    solution30.test();
//    Solution31 solution31 = Solution31();
//    solution31.test();
//    Solution32 solution32 = Solution32();
//    solution32.test();
//    Solution33 solution33 = Solution33();
//    solution33.test();
//    Solution34 solution34 = Solution34();
//    solution34.test();
//    Solution35 solution35 = Solution35();
//    solution35.test();
//    Solution36 solution36 = Solution36();
//    solution36.test();
    Solution37 solution37 = Solution37();
    solution37.test();
    return 0;
}
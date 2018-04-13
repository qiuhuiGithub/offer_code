//
// Created by qiu hui on 2017/9/2.
//
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
#include <set>

using namespace std;

//树的最长路径
class Solution1 {
public:
    struct TreeNode {
        int val;
        TreeNode *pleft;
        TreeNode *pright;
        int leftMaxValue;
        int rightMaxValue;

        TreeNode(int x) : val(x), pleft(NULL), pright(NULL), leftMaxValue(0), rightMaxValue(0) {}
    };

    void findMaxLen(TreeNode *root, int *maxLen) {
        //遍历到叶子结点，返回
        if (root == NULL)
            return;

        //如果左子树为空，那么该节点左边最长距离为0
        if (root->pleft == NULL)
            root->leftMaxValue = 0;

        //如果右子树为空，那么该节点右边最长距离为0
        if (root->pright == NULL)
            root->rightMaxValue = 0;

        //如果左子树不为空，递归寻找左子树最长距离
        if (root->pleft != NULL)
            findMaxLen(root->pleft, maxLen);

        //如果右子树不为空，递归寻找右子树最长距离
        if (root->pright != NULL)
            findMaxLen(root->pright, maxLen);

        //计算左子树中距离根节点的最长距离
        if (root->pleft != NULL) {
            if (root->pleft->leftMaxValue > root->pleft->rightMaxValue)
                root->leftMaxValue = root->pleft->leftMaxValue + 1;
            else
                root->leftMaxValue = root->pleft->rightMaxValue + 1;
        }

        //计算右子树中距离根节点的最长距离
        if (root->pright != NULL) {
            if (root->pright->leftMaxValue > root->pright->rightMaxValue)
                root->rightMaxValue = root->pright->leftMaxValue + 1;
            else
                root->rightMaxValue = root->pright->rightMaxValue + 1;
        }

        //更新最长距离
        if (root->leftMaxValue + root->rightMaxValue > *maxLen)
            *maxLen = root->leftMaxValue + root->rightMaxValue;
    }

    void test() {
        TreeNode *root = new TreeNode(1);
        root->pleft = new TreeNode(2);
        root->pright = new TreeNode(3);
        root->pleft->pleft = new TreeNode(4);
        root->pleft->pright = new TreeNode(5);
        int maxlen = 0;
        findMaxLen(root, &maxlen);
        cout << maxlen << endl;
    }

};

//输入节点数，输出有多少棵不同的二叉树
class Solution2 {
public:
    int numTrees(int n) {
        if (n <= 1)
            return 1;
        int uniqueBST = 0;
        for (int i = 1; i <= n; i++) {
            uniqueBST += numTrees(i - 1) * numTrees(n - i);
        }
        return uniqueBST;
    }

    void test() {
        cout << numTrees(3) << endl;
    }
};


//和为某一特定值的路径
class Solution3 {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> result;
        vector<int> path;
        if (root == NULL)
            return result;
        int curSum = 0;
        pathSum(root, sum, curSum, path, result);
        return result;

    }

    void pathSum(TreeNode *root, int sum, int curSum, vector<int> &path, vector<vector<int>> &result) {
        curSum += root->val;
        path.push_back(root->val);
        bool isLeaf = (root->left == NULL) && (root->right == NULL);
        if (curSum == sum && isLeaf) {
            result.push_back(path);
        }
        if (root->left != NULL)
            pathSum(root->left, sum, curSum, path, result);
        if (root->right != NULL)
            pathSum(root->right, sum, curSum, path, result);
        path.pop_back();
    }

    void test() {
        TreeNode *root = new TreeNode(10);
        root->left = new TreeNode(5);
        root->right = new TreeNode(12);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(7);
        pathSum(root, 22);
    }
};

//树的最浅节点
class Solution4 {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    int run(TreeNode *root) {
        if (root == NULL)
            return 0;
        if (root->left == NULL && root->right == NULL)
            return 1;
        if (root->left == NULL)
            return run(root->right) + 1;
        if (root->right == NULL)
            return run(root->left) + 1;
        return min(run(root->left), run(root->right)) + 1;
    }

    void test() {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        cout << run(root);
    }
};

int main() {
//    Solution1 solution1;
//    solution1.test();
    Solution3 solution3;
    solution3.test();
    return 0;
}
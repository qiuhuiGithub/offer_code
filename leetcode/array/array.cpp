//
// Created by qiu hui on 2017/8/30.
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

//最长连续子数组
class Solution1 {
public:

    int longestConsecutive(vector<int> &num) {
        unordered_set<int> myset(num.begin(), num.end());
        int res = 1;
        for (int current:num) {
            if (myset.find(current) == myset.end()) continue;

            myset.erase(current);
            int prev = current - 1, post = current + 1;
            while (myset.find(prev) != myset.end()) {
                myset.erase(prev--);
            }
            while (myset.find(post) != myset.end()) {
                myset.erase(post++);
            }
            res = max(res, post - prev - 1);
        }
        return res;
    }

    void test() {
        vector<int> num;
        num.push_back(100);
        num.push_back(1);
        num.push_back(2);
        num.push_back(3);
        num.push_back(4);
        num.push_back(200);
        cout << longestConsecutive(num);
    }
};


//排序数组转平衡二叉树
class Solution2 {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    TreeNode *sortedArrayToBST(vector<int> &num, int begin, int end) {
        if (begin >= end) {
            return NULL;
        }
        int mid = (begin + end) / 2;
        TreeNode *root = new TreeNode(num[mid]);
        root->left = sortedArrayToBST(num, begin, mid);
        root->right = sortedArrayToBST(num, mid + 1, end);
        return root;
    }

    TreeNode *sortedArrayToBST(vector<int> &num) {
        if (num.empty()) {
            return NULL;
        }
        return sortedArrayToBST(num, 0, num.size());

    }

    void test() {
        vector<int> num;
        num.push_back(1);
        num.push_back(2);
        num.push_back(3);
        TreeNode *root = sortedArrayToBST(num);
    }
};


//3sum，从数组中找三个数，使得它们的和为0
class Solution6 {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > result;
        int len = num.size();
        if (len < 3) return result;
        sort(num.begin(), num.end());

        vector<int> temp(3);
        for (int i = 0; i < len; i++) {
            if (i == 0 || num[i] != num[i - 1]) {
                int left = i + 1;
                int right = len - 1;
                while (left < right) {
                    while (left < right && num[i] + num[left] + num[right] > 0)
                        right--;
                    if (left < right && num[left] + num[right] + num[i] == 0) {
                        temp[0] = num[i];
                        temp[1] = num[left];
                        temp[2] = num[right];
                        result.push_back(temp);
                        while (left < right && num[left] == temp[1]) left++;
                    } else
                        left++;
                }
            }
        }
        return result;
    }

    void test() {
        vector<int> num;
        num.push_back(-1);
        num.push_back(0);
        num.push_back(1);
        num.push_back(2);
        num.push_back(-1);
        num.push_back(-4);
        vector<vector<int>> result = threeSum(num);
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[i].size(); j++) {
                cout << result[i][j];
            }
            cout << endl;
        }
    }
};


//3sum closest,任意三个数的和距离目标值最近
class Solution3 {
public:
    int threeSumClosest(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        int n = num.size();
        int cur = num[0] + num[1] + num[n - 1];
        for (int i = 0; i < n - 2; i++) {
            int start = i + 1;
            int end = n - 1;
            while (start < end) {
                int sum = num[i] + num[start] + num[end];
                if (sum < target)
                    start++;
                else {
                    end--;
                }
                if (abs(sum - target) < abs(cur - target))
                    cur = sum;
            }
        }
        return cur;
    }

    void test() {
        vector<int> num;
        num.push_back(-1);
        num.push_back(1);
        num.push_back(2);
        num.push_back(-4);
        int target = 1;
        cout << threeSumClosest(num, target);
    }
};

//最大储水量，木板无宽度
class Solution4 {
public:
    int maxArea(vector<int> &height) {
        int max = 0;
        int n = height.size();
        if (n < 2)
            return 0;
        int l = 0;
        int r = n - 1;
        while (l < r) {
            int sum = (r - l) * min(height[l], height[r]);
            if (sum > max)
                max = sum;
            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }
        return max;
    }

    void test() {
        vector<int> height;
        height.push_back(1);
        height.push_back(2);
        height.push_back(3);
        height.push_back(4);
        height.push_back(1);
        cout << maxArea(height);
    }
};

//最大储水量，木板宽度为1
class Solution5 {
public:
    int trap(int A[], int n) {
        int sum = 0;
        //找最大下标
        int maxIndex = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] > A[maxIndex])
                maxIndex = i;
        }
        int left = 0;
        for (int i = 0; i < maxIndex; i++) {
            if (A[i] < A[left]) {
                sum += A[left] - A[i];
            } else {
                left = i;
            }
        }
        int right = n - 1;
        for (int i = n - 1; i > maxIndex; i--) {
            if (A[i] < A[right]) {
                sum += A[right] - A[i];
            } else {
                right = i;
            }
        }
        return sum;
    }

    void test() {
        int n = 12;
        int A[12] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        cout << trap(A, n);
    }
};

//电话号码组合:输入电话号码，输出所有可能打印出的字母组合
class Solution6 {
public:
    string dic[10] = {{""},
                      {""},
                      {"abc"},
                      {"def"},
                      {"ghi"},
                      {"jkl"},
                      {"mno"},
                      {"pqrs"},
                      {"tuv"},
                      {"wxyz"}};

    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.size() == 0)
            return result;
        string word;
        dfs(digits, result, word, 0);
        return result;
    }

    void dfs(string digits, vector<string> &result, string &word, int index) {
        if (word.size() == digits.size()) {
            result.push_back(word);
            return;
        }
        for (int i = 0; i < dic[digits[index] - '0'].size(); i++) {
            word.push_back(dic[digits[index] - '0'][i]);
            dfs(digits, result, word, index + 1);
            word.pop_back();
        }
    }

    void test() {
        string digits = "23";
        vector<string> result = letterCombinations(digits);
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << endl;
        }
    }
};

//最大子数组和
class Solution7 {
public:
    int maxSubArray(int A[], int n) {
        int max = 0x80000000;
        if (n <= 0)
            return max;
        int curSum = 0;
        for (int i = 0; i < n; i++) {
            if (curSum <= 0)
                curSum = A[i];
            else
                curSum += A[i];
            if (curSum > max)
                max = curSum;
        }
        return max;
    }

    void test() {
        int A[5] = {-2, -1, 3, 4, -2};
        cout << maxSubArray(A, 5);
    }
};

//给定一个数组，找出数组所有的子集。回溯。
class Solution8 {
public:
    vector<vector<int>> subsets(vector<int> &S) {
        vector<vector<int>> res;
        vector<int> v;
        sort(S.begin(), S.end());
        for (int j = 0; j <= S.size(); j++) {
            backtracking(res, S, j, 0, v);
        }
        return res;
    }

    void backtracking(vector<vector<int>> &res, vector<int> &S, int k, int start, vector<int> v) {
        if (k < 0) return;
        else if (k == 0)
            res.push_back(v);
        else {
            for (int i = start; i < S.size(); i++) {
                v.push_back(S[i]);
                backtracking(res, S, k - 1, i + 1, v);
                v.pop_back();
            }
        }
    }

    void test() {
        vector<int> vector1;
        vector1.push_back(1);
        vector1.push_back(2);
        vector<vector<int>> result = subsets(vector1);
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[i].size(); j++) {
                cout << result[i][j];
            }
            cout << endl;
        }
    }

};

int main() {
//    Solution2 solution2 = Solution2();
//    solution2.test();
    Solution6 solution6;
    solution6.test();
    return 0;
}

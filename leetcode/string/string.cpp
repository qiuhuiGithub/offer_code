//
// Created by qiu hui on 2017/8/14.
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

//将一个长字符串切分成子串，使得每一个子串都是回文的。
class Solution1 {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string> > ret;
        if (s.empty()) return ret;

        vector<string> path;
        dfs(0, s, path, ret);

        return ret;
    }

    void dfs(int index, string &s, vector<string> &path, vector<vector<string> > &ret) {
        if (index == s.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = index; i < s.size(); ++i) {
            if (isPalindrome(s, index, i)) {
                path.push_back(s.substr(index, i - index + 1));
                dfs(i + 1, s, path, ret);
                path.pop_back();
            }
        }
    }

    bool isPalindrome(const string &s, int start, int end) {
        while (start <= end) {
            if (s[start++] != s[end--])
                return false;
        }
        return true;
    }

    void test() {
        string s = "aab";
        vector<vector<string>> result;
        result = partition(s);
    }
};

//二进制加法
class Solution2 {
public:
    string addBinary(string a, string b) {
        int length = a.length() > b.length() ? a.length() : b.length();
        while (a.length() > b.length())
            b = "0" + b;
        while (a.length() < b.length())
            a = "0" + a;
        unsigned int carry = 0;
        string result;
        for (int i = length - 1; i >= 0; i--) {
            if (a[i] - '0' + b[i] - '0' == 1) {
                if (carry == 1) {
                    result = "0" + result;
                    carry = 1;
                } else {
                    result = "1" + result;
                    carry = 0;
                }
            } else if (a[i] - '0' + b[i] - '0' == 2) {
                if (carry == 1) {
                    result = "1" + result;
                    carry = 1;
                } else {
                    result = "0" + result;
                    carry = 1;
                }
            } else {
                if (carry == 1) {
                    result = "1" + result;
                    carry = 0;
                } else {
                    result = "0" + result;
                    carry = 0;
                }
            }
        }
        if (carry) {
            result = "1" + result;
        }
        return result;
    }

    void test() {
        string a = "11";
        string b = "1";
        cout << addBinary(a, b);
    }
};

//正则表达式匹配和通配符匹配
class Solution3 {
public:
    //正则表达式匹配
    bool isMatch(const char *s, const char *p) {
        if (*p == '\0') return *s == '\0';
        if (*(p + 1) == '*') {

            while ((*p == *s) || (*p == '.' && *s != '\0')) {

                if (isMatch(s, p + 2))
                    return true;
                s++;
            }

            return isMatch(s, p + 2);
        } else {

            if ((*p == *s) || (*p == '.' && *s != '\0')) {
                return isMatch(s + 1, p + 1);
            } else {
                return false;
            }
        }
    }

    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        if (p.size() == 1) {
            return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
        }
        if (p[1] != '*') {
            if (s.empty()) return false;
            return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
        }
        while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
            if (isMatch(s, p.substr(2))) return true;
            s = s.substr(1);
        }
        return isMatch(s, p.substr(2));
    }

    bool isMatch1(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*')
                dp[0][i] = dp[0][i - 1];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }

    //通配符匹配
    bool isMatch2(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*') dp[0][i] = dp[0][i - 1];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }

    void test() {
        string s = "baa";
        string p = "b*";
        cout << isMatch(s, p);
    }

};

//最长不重复子序列
class Solution4 {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> dp(128, 0);
        vector<int> loc(128, 0);
        int max = 0;
        int length = 0;
        for (int i = 0; i < s.size();) {
            if (dp[s[i]] == 0) {
                dp[s[i]] = 1;
                loc[s[i]] = i;
                length++;
                i++;

            } else {
                if (length > max) {
                    max = length;
                }
                for (int i = 0; i < 128; i++)
                    dp[i] = 0;
                length = 0;
                i = loc[s[i]] + 1;
            }
        }
        if (length > max)
            max = length;
        return max;
    }

    void test() {
        string s = "abcabca";
        cout << lengthOfLongestSubstring(s);
    }
};

//最长回文子串
class Solution5 {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        string res = "";
        vector<vector<int>> dp(50, vector<int>(50, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                dp[i][j] = s[i] == s[j] && (j - i < 3 || dp[i + 1][j - 1]);

                if (dp[i][j] && (res.empty() || j - i + 1 > res.length())) {
                    res = s.substr(i, j + 1 - i);
                }
            }
        }
        return res;
    }

    void test() {
        string s = "aba";
        cout << longestPalindrome(s);
    }
};

//Z字型打印
class Solution6 {
public:
    string convert(string s, int nRows) {
        if (nRows == 1)
            return s;
        int len = s.size();
        vector<string> z(nRows, "");
        int dir = 1;
        int row = 0;
        for (int i = 0; i < len; i++) {
            z[row] += s[i];
            if (row == 0)
                dir = 1;
            else if (row == nRows - 1)
                dir = -1;
            row += dir;
        }
        string result = "";
        for (int i = 0; i < nRows; i++) {
            result += z[i];
        }
        return result;
    }

    void test() {
        string s = "ABCD";
        cout << convert(s, 3);
    }
};

//罗马数字转数字
class Solution7 {
public:
    int romanToInt(string s) {
        map<char, int> map1;
        map1['I'] = 1;
        map1['X'] = 10;
        map1['C'] = 100;
        map1['D'] = 500;
        map1['V'] = 5;
        map1['L'] = 50;
        map1['M'] = 1000;

        int len = s.size();
        int sum = 0;
        for (int i = 0; i < len - 1; ++i) {
            int temp = map1[s[i]];
            int temp2 = map1[s[i + 1]];
            if (temp < temp2)
                sum -= temp;
            else
                sum += temp;
        }
        return sum + map1[s[len - 1]];
    }

    void test() {
        string s = "XX";
        cout << romanToInt(s);
    }
};

//字符串数组的最长公共前缀
class Solution8 {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty())
            return "";
        sort(strs.begin(), strs.end());

        int n = strs.size();
        int l = min(strs[0].size(), strs[n - 1].size());
        for (int i = 0; i < l; i++)
            if (strs[0][i] != strs[n - 1][i])
                return strs[0].substr(0, i);
        return strs[0].substr(0, l);
    }

    void test() {
        vector<string> str;
        str.push_back("c");
        str.push_back("abc");
        str.push_back("cab");
        cout << longestCommonPrefix(str);
    }
};


int main() {
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
    Solution7 solution7 = Solution7();
    solution7.test();
}
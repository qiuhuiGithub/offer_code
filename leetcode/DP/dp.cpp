//
// Created by qiu hui on 2017/8/3.
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

#define MAXN 10
#define INT_MAX 0x7fffffff
#define INT_MIN 0x80000000

//一组小朋友站一排，每个人有一个值，为小朋友分配糖，1.使得每个小朋友至少一颗糖；2.值越大的小朋友分配的糖比他的邻居多，最少需要多少糖
class Solution1 {
public:
    int candy(vector<int> &ratings) {
        int length = ratings.size();
        if (length == 1) return 1;
        vector<int> dp(length, 1);
        for (int i = 0; i < length - 1; i++) {
            if (ratings[i] < ratings[i + 1])
                dp[i + 1] = dp[i] + 1;
        }
        for (int j = length - 1; j > 0; j--) {
            if (ratings[j] < ratings[j - 1] && dp[j] >= dp[j - 1])
                dp[j - 1] = dp[j] + 1;
        }
        int sum = 0;
        for (vector<int>::iterator it = dp.begin(); it != dp.end(); it++) {
            sum += *it;
        }
        return sum;
    }

    void test() {
        vector<int> ratings = {1, 2, 3, 2, 1};
        cout << candy(ratings);
    }
};

//字符串分隔，判断分隔完能否使得每个部分都出现在词典中
class Solution2 {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        int length = s.length();
        vector<bool> dp(length + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.length(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (dp[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[length];
    }

    void test() {
        unordered_set<string> dict;
        dict.insert("leet");
        dict.insert("code");
        cout << wordBreak("leetcode", dict);
    }
};


//两字符串的最小编辑距离
class Solution3 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min3(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + 1);
            }
        }
        return dp[m][n];
    }

    void test() {
        string word1 = "abc";
        string word2 = "ab";
        cout << minDistance(word1, word2);
    }
};


int main() {
    Solution1 solution1 = Solution1();
    solution1.test();
    return 0;
}

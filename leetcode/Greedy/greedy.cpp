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

//找出三角形自顶向下最小的路径和
class Solution1 {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int row = triangle.size();
        for (int i = row - 2; i >= 0; i--) {
            for (int j = 0; j < triangle[i].size(); j++) {
                triangle[i][j] += triangle[i + 1][j] > triangle[i + 1][j + 1] ? triangle[i + 1][j] : triangle[i + 1][j];
            }
        }
        return triangle[0][0];
    }

    void test() {
        vector<vector<int> > triangle;
        vector<int> vector1 = {2};
        vector<int> vector2 = {3, 4};
        vector<int> vector3 = {6, 5, 7};
        vector<int> vector4 = {4, 1, 8, 3};
        triangle.push_back(vector1);
        triangle.push_back(vector2);
        triangle.push_back(vector3);
        triangle.push_back(vector4);
        cout << minimumTotal(triangle);
    }
};

//股票最大收益
class Solution2 {
public:
    int max(int a, int b) {
        return a > b ? a : b;
    }

    //只能卖一次
    int maxProfit1(vector<int> &prices) {
        int ans = 0;
        int Min = 0x7fffffff;
        for (int i = 0; i < prices.size(); i++) {
            ans = ans > prices[i] - Min ? ans : prices[i] - Min;
            Min = Min < prices[i] ? Min : prices[i];
        }
        return ans;
    }

    //可以卖多次
    int maxProfit2(vector<int> &prices) {
        int ans = 0;
        for (int i = 0; i < prices.size() - 1; i++) {
            if (prices[i + 1] > prices[i]) {
                ans += prices[i + 1] - prices[i];
            }
        }
        return ans;
    }

    //只能卖两次
    int maxProfit3(vector<int> &prices) {
        int sell1 = 0, sell2 = 0, buy1 = 0x80000000, buy2 = 0x80000000;
        for (int i = 0; i < prices.size(); i++) {
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }
        return sell2;
    }

    void test() {
        vector<int> prices;
        prices.push_back(1);
        prices.push_back(2);
        prices.push_back(8);
        prices.push_back(3);
        cout << maxProfit3(prices);
    }
};

//加油站，找到一个加油站，绕所有的加油站一圈，使得能回到原点，没有返回-1.
class Solution3 {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int sum = 0, start = 0, total = 0;
        if (gas.size() == 0 || cost.size() == 0 || gas.size() != cost.size())
            return -1;
        for(int i=0;i<gas.size();i++){
            total += gas[i]-cost[i];
            if(sum<0){
                sum = gas[i]- cost[i];
                start = i;
            }else{
                sum += gas[i] - cost[i];
            }
        }
        return total<0?-1:start;
    }

    void test() {

    }

};

int main() {
    Solution1 solution1 = Solution1();
    solution1.test();
    return 0;
}

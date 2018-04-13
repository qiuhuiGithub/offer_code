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

//给定一个数组,找出所有的排列数
class Solution1 {
public:
    vector<vector<int> > permute(vector<int> &num) {
        int size = num.size();
        vector<vector<int> > result;
        return perm(num, 0, size, result);
    }

    vector<vector<int> > perm(vector<int> &num, int k, int m, vector<vector<int> > &result) {
        if (k == m) {
            vector<int> temp;
            for (int i = 0; i < m; i++) {
                temp.push_back(num[i]);
            }
            result.push_back(temp);
        } else {
            for (int i = k; i < m; i++) {
                swap(&num[k], &num[i]);
                perm(num, k + 1, m, result);
                swap(&num[k], &num[i]);
            }
        }
        set<vector<int>> resultSet;
        for (int i = 0; i < result.size(); i++) {
            resultSet.insert(result[i]);
        }
        result.clear();
        set<vector<int>>::iterator it = resultSet.begin();
        for (; it != resultSet.end(); it++) {
            result.push_back(*it);
        }
        return result;

    }

    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void test() {
        vector<int> num;
        num.push_back(1);
        num.push_back(1);
        num.push_back(2);
        vector<vector<int>> result;
        result = permute(num);
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < 3; j++)
                cout << result[i][j];
            cout << endl;
        }
    }
};

//非递归快速排序
class Solution2 {
public:
    int partition(vector<int> &numbers, int start, int end) {
        if (numbers.empty())
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

    void nonRec_quickSort(vector<int> &numbers, int start, int end) {
        stack<int> s;
        if (start < end) {
            s.push(end);
            s.push(start);
            while (!s.empty()) {
                int l = s.top();
                s.pop();
                int r = s.top();
                s.pop();
                int index = partition(numbers, l, r);
                if (l < index - 1) {
                    s.push(index - 1);
                    s.push(l);
                }
                if (r > index + 1) {
                    s.push(r);
                    s.push(index + 1);
                }
            }
        }
    }

    void test() {
        vector<int> numbers;
        numbers.push_back(1);
        numbers.push_back(6);
        numbers.push_back(2);
        numbers.push_back(4);
        nonRec_quickSort(numbers, 0, numbers.size());
        for (int i = 0; i < 4; i++) {
            cout << numbers[i];
        }
    }
};

int main() {
    Solution1 solution1 = Solution1();
    solution1.test();
}


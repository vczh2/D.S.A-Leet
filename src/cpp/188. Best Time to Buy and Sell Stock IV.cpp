/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Credits:
Special thanks to @Freezen for adding this problem and creating all test cases.
*/

#include <common.hpp>
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
    }
};

/*
dp
status:
profit[day_index][transactions][hold] transaction:0,1,2,...,k hold:0,1
*/

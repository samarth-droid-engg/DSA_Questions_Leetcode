class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int buy = prices[0], sell = 0;
        int maxSell = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] < buy) {
                buy = prices[i];
                sell = prices[i] - buy;
            }
            if ((prices[i] - buy) >= 0)
                maxSell = max(maxSell, max(sell, prices[i]-buy));
        }
        return maxSell;
    }
};
class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int freq[26] = {};
            for (int j = i; j < n; j++) {
                freq[s[j] - 'a']++;

                int minF = INT_MAX;
                int maxF = 0;

                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        maxF = max(maxF, freq[k]);
                        minF = min(minF, freq[k]);
                    }
                }
                sum += (maxF - minF);
            }
        }
        return sum;
    }
};
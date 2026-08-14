class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        int freq[26] = {};
        int left = 0, maxSize = INT_MIN;
        for (int right = 0; right < n; right++) {
            int idx = s[right] - 'a';
            freq[idx]++;
            while(freq[idx]>2){
                freq[s[left] - 'a']--;
                left++;
            }
            maxSize = max(maxSize, right - left + 1);
        }
        return maxSize;
    }
};
class Solution {
public:
    void expand(string& s, int left, int right, string& ans) {

        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }

        int len = right - left - 1;

        if (len > ans.size()) {
            ans = s.substr(left + 1, len);
        }
    }

    string longestPalindrome(string s) {

        string ans = "";

        for (int i = 0; i < s.size(); i++) {

            // Odd length palindrome
            expand(s, i, i, ans);

            // Even length palindrome
            expand(s, i, i + 1, ans);
        }
        return ans;
    }
};
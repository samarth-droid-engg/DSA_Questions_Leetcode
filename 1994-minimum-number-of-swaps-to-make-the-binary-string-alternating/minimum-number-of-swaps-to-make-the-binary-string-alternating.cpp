class Solution {
public:
    int countSwaps(string& s, char start) {
        int mismatch = 0;
        char expected = start;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != expected)
                mismatch++;
            expected = (expected == '0') ? '1' : '0';
        }
        return mismatch / 2;
    }
    int minSwaps(string s) {
        int zero = 0, one = 0;

        for (char c : s) {
            if (c == '0')
                zero++;
            else
                one++;
        }
        if (abs(zero - one) > 1) {
            return -1;
        }
        if (zero > one) {
            return countSwaps(s, '0');
        }
        if (one > zero) {
            return countSwaps(s, '1');
        }
        return min(countSwaps(s, '0'), countSwaps(s, '1'));
    }
};
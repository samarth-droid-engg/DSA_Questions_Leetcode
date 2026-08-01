class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int num = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'I') {
                num++;
            } else if (s[i] == 'V') {
                if (i - 1 >= 0 && s[i - 1] == 'I') {
                    num -= 2;
                }
                num += 5;
            } else if (s[i] == 'X') {
                if (i - 1 >= 0 && s[i - 1] == 'I') {
                    num -= 2;
                }
                num += 10;
            } else if (s[i] == 'L') {
                if (i - 1 >= 0 && s[i - 1] == 'X') {
                    num -= 20;
                }
                num += 50;
            } else if (s[i] == 'C') {
                if (i - 1 >= 0 && s[i - 1] == 'X') {
                    num -= 20;
                }
                num += 100;
            } else if (s[i] == 'D') {
                if (i - 1 >= 0 && s[i - 1] == 'C') {
                    num -= 200;
                }
                num += 500;
            } else if (s[i] == 'M') {
                if (i - 1 >= 0 && s[i - 1] == 'C') {
                    num -= 200;
                }
                num += 1000;
            }
        }
        return num;
    }
};
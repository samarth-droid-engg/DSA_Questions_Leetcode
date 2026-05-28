class Solution {
public:
    int numberOfSpecialChars(string word) {
        int len = word.size();
        set<char> s;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                char ch = word[i];
                if (isupper(ch)) {
                    if ((ch + 'a' - 'A') == word[j])
                        s.insert(ch+'a'-'A');
                } else {
                    if ((ch - 'a' + 'A') == word[j])
                        s.insert(ch);
                }
            }
        }
        return s.size();
    }
};
class Solution {
public:
    int numberOfSpecialChars(string word) {
        int len = word.size();
        map<char, int> firstUpper; // first uppercase index
        map<char, int> lastLower;  // last lowercase index

        for (int i = 0; i < len; i++) {
            char ch = word[i];
            if (isupper(ch)) {
                if (firstUpper.find(ch) == firstUpper.end())
                    firstUpper[ch] = i; // store only FIRST uppercase
            } else {
                lastLower[ch] = i; // gives LAST lowercase
            }
        }

        int count = 0;
        for (auto& [upperCh, upperIdx] : firstUpper) {
            char lowerCh = upperCh - 'A' + 'a';
            // both must exist AND last lowercase < first uppercase
            if (lastLower.count(lowerCh) && lastLower[lowerCh] < upperIdx)
                count++;
        }
        return count;
    }
};
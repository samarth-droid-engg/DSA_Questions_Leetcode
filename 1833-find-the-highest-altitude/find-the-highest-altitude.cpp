class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int maxA = 0;
        int currA = 0;
        for (int i = 0; i < gain.size(); i++) {
            currA += gain[i];
            maxA = max(maxA, currA);
        }
        return maxA;
    }
};
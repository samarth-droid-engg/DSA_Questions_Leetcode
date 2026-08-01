class Solution {
    using ll = long long;

    bool isPossible(ll initial, vector<int> &monsters, vector<ll> &bonus) {
        for(int i = 0; i < monsters.size(); i++) {
            ll total = initial + bonus[i];
            
            if(total >= monsters[i]) {
                initial -= monsters[i];
                if(initial < 0) initial = 0;
            } else {
                return false;
            }
        }
        
        return true;
    }
    
public:
    long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts) {
        int n = monsters.size();
        
        vector<ll> diff(n+1, 0);
        for(auto &b : boosts) {
            diff[b[0]] += b[2];
            if(b[1] + 1 < n) diff[b[1] + 1] -= b[2];
        }

        vector<ll> bonus(n);
        ll curr = 0;
        for(int i = 0; i < n; i++) {
            curr += diff[i];
            bonus[i] = curr;
        }

        ll low = 0;
        ll high = accumulate(monsters.begin(), monsters.end(), 0LL);

        while(low <= high) {
            ll mid = low + (high - low) / 2;
            if(isPossible(mid, monsters, bonus)) high = mid - 1;
            else low = mid + 1;
        }

        return low;
    }
};
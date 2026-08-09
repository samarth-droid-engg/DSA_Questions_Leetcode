class MinStack {
public:
    vector<pair<int, int>> vt;
    int minE = INT_MAX;
    MinStack() {}

    void push(int value) {
        if (vt.empty()) {
            vt.push_back({value, value});
            minE = min(minE, value);
            return;
        } else {
            minE = min(minE, value);
            vt.push_back({value, minE});
        }
    }

    void pop() {
        vt.pop_back();
        if (!vt.empty())
            minE = vt.back().second;
    }

    int top() { return vt.back().first; }

    int getMin() { return vt.back().second; }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
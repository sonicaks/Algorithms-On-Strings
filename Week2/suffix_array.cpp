#include <bits/stdc++.h>

using namespace std;

char ch[5] = {'$', 'A', 'C', 'G', 'T'};

vector<int> sortCharacters(string s) {
    int n = (int)s.length();
    vector<int> order(n, 0);
    vector<int> count(5, 0);
    for (int i = 0; i < n; i++) {
        int idx = lower_bound(ch, ch + 5, s[i]) - ch;
        count[idx]++;
    }
    for (int i = 1; i < 5; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int idx = lower_bound(ch, ch + 5, s[i]) - ch;
        count[idx]--;
        order[count[idx]] = i;
    }
    return order;
}

vector<int> computeCharClasses(string s, vector<int> &order) {
    int n = (int)s.length();
    vector<int> eqClass(n, 0);
    eqClass[order[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[order[i]] == s[order[i - 1]]) {
            eqClass[order[i]] = eqClass[order[i - 1]];
        } else {
            eqClass[order[i]] = eqClass[order[i - 1]] + 1;
        }
    }
    return eqClass;
}

vector<int> sortDoubled(vector<int> &order, vector<int> &eqClass, int l) {
    int n = (int)order.size();
    vector<int> newOrder(n, 0);
    vector<int> count(n, 0);
    for (int i = 0; i < n; i++) {
        count[eqClass[i]]++;
    }
    for (int i = 1; i < n; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int st = (order[i] - l + n) % n;
        count[eqClass[st]]--;
        newOrder[count[eqClass[st]]] = st;
    }
    return newOrder;
}

vector<int> updateCharClasses(vector<int> &newOrder, vector<int> &eqClass, int l) {
    int n = (int)newOrder.size();
    vector<int> newEqClass(n, 0);
    newEqClass[newOrder[0]] = 0;
    for (int i = 1; i < n; i++) {
        int cur = newOrder[i];
        int pre = newOrder[i - 1];
        int curMid = (cur + l) % n;
        int preMid = (pre + l) % n;
        if (eqClass[cur] == eqClass[pre] and eqClass[curMid] == eqClass[preMid]) {
            newEqClass[cur] = newEqClass[pre];
        } else {
            newEqClass[cur] = newEqClass[pre] + 1;
        }
    }
    return newEqClass;
}

vector<int> buildSuffixArray(string s) {
    int n = (int)s.length();
    int l = 1;
    vector<int> order = sortCharacters(s);
    vector<int> eqClass = computeCharClasses(s, order);
    while (l < n) {
        order = sortDoubled(order, eqClass, l);
        eqClass = updateCharClasses(order, eqClass, l);
        l *= 2;
    }
    return order;
}

void solve() {
    string s;
    cin >> s;
    vector<int> order = buildSuffixArray(s);
    for (int i = 0; i < (int)order.size(); i++) {
        cout << order[i] << " ";
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
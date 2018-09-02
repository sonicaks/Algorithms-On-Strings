#include <bits/stdc++.h>

using namespace std;

char ch[5] = {'$', 'A', 'C', 'G', 'T'};

vector<int> sortCharacters(string s) {
    int n = (int)s.length();
    vector<int> order(n);
    vector<int> count(5, 0);
    for (int i = 0; i < n; i++) {
        int c = lower_bound(ch, ch + 5, s[i]) - ch;
        count[c]++;
    }
    for (int i = 1; i < 5; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int c = lower_bound(ch, ch + 5, s[i]) - ch;
        count[c]--;
        order[count[c]] = i;
    }
    return order;
}

vector<int> computeCharClasses(string s, vector<int> &order) {
    int n = (int)s.length();
    vector<int> eqClass(n);
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
    vector<int> newOrder(n);
    vector<int> count(n, 0);
    for (int i = 0; i < n; i++) {
        count[eqClass[i]]++;
    }
    for (int i = 1; i < n; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int st = (order[i] - l + n) % n;
        int cl = eqClass[st];
        count[cl]--;
        newOrder[count[cl]] = st;
    }
    return newOrder;
}

vector<int> updateCharClasses(vector<int> &order, vector<int> &eqClass, int l) {
    int n = (int)order.size();
    vector<int> newEqClass(n, 0);
    newEqClass[order[0]] = 0;
    for (int i = 1; i < n; i++) {
        int cur = order[i];
        int pre = order[i - 1];
        int curMid = (cur + l) % n;
        int preMid = (pre + l) % n;
        if ((eqClass[cur] == eqClass[pre]) and (eqClass[curMid] == eqClass[preMid])) {
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
    while (l <= n) {
        order = sortDoubled(order, eqClass, l);
        eqClass = updateCharClasses(order, eqClass, l);
        l *= 2;
    }
    return order;
}

void solve() {
    string s;
    cin >> s;
    int n = (int)s.length();
    vector<int> order = buildSuffixArray(s);
    for (int i = 0; i < n; i++) {
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
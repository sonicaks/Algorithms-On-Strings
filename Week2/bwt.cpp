#include <bits/stdc++.h>

using namespace std;

char ch[5] = {'$', 'A', 'C', 'G', 'T'};

void solve() {
    string s;
    cin >> s;
    deque<char> dq;
    vector<string> v;
    int n = (int)s.length();
    for (int i = 0; i < n; i++) {
        dq.push_back(s[i]);
    }
    for (int i = 0; i < n; i++) {
        string t = "";
        for (int j = 0; j < (int)dq.size(); j++) {
            t += dq[j];
        }
        v.push_back(t);
        dq.push_front(dq.back());
        dq.pop_back();
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        cout << v[i][n - 1];
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
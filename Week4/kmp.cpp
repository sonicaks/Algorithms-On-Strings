#include <bits/stdc++.h>

using namespace std;

string pat, txt;

vector<int> computeLCP(string s) {
    int n = s.length();
    vector<int> lcp(n, 0);
    int border = 0;
    for (int i = 1; i < n; i++) {
        while (border > 0 and (s[i] != s[border])) {
            border = lcp[border - 1];
        }
        if (s[i] == s[border]) border = border + 1;
        else border = 0;
        lcp[i] = border;
    }
    return lcp;
}

void solve() {
    cin >> pat >> txt;
    vector<int> res = computeLCP(pat + '$' + txt);
    int n = (int)pat.length();
    for (int i = 0; i < res.size(); i++) {
        if (res[i] == n) {
            cout << i - 2 * n << " ";
        }
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
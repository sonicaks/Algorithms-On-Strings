#include <bits/stdc++.h>

using namespace std;

char ch[5] = {'$', 'A', 'C', 'G', 'T'};
string txt, pat;

vector<int> sortCharacters() {
    int n = (int)txt.length();
    vector<int> order(n);
    vector<int> count(5, 0);
    for (int i = 0; i < n; i++) {
        int c = lower_bound(ch, ch + 5, txt[i]) - ch;
        count[c]++;
    }
    for (int i = 1; i < 5; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int c = lower_bound(ch, ch + 5, txt[i]) - ch;
        count[c]--;
        order[count[c]] = i;
    }
    return order;
}

vector<int> computeCharClasses(vector<int> &order) {
    int n = (int)txt.length();
    vector<int> eqClass(n);
    eqClass[order[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (txt[order[i]] == txt[order[i - 1]]) {
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
        count[eqClass[st]]--;
        newOrder[count[eqClass[st]]] = st;
    }
    return newOrder;
}

vector<int> updateCharClasses(vector<int> &order, vector<int> &eqClass, int l) {
    int n = (int)order.size();
    vector<int> newEqClass(n);
    newEqClass[order[0]] = 0;
    for (int i = 1; i < n; i++) {
        int cur = order[i];
        int pre = order[i - 1];
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

vector<int> buildSuffixArray() {
    int n = (int)txt.length();
    int l = 1;
    vector<int> order = sortCharacters();
    vector<int> eqClass = computeCharClasses(order);
    while (l < n) {
        order = sortDoubled(order, eqClass, l);
        eqClass = updateCharClasses(order, eqClass, l);
        l *= 2;
    }
    return order;
}

int chk(int mid, vector<int> &order) {
    int i = 0;
    int j = order[mid];
    int ok = 1;
    while (i < (int)pat.length() and j < (int)txt.length()) {
        if (pat[i] == txt[j]) {
            i++;
            j++;
        } else if (pat[i] < txt[j]) {
            ok = -1;
            break;
        } else {
            ok = 1;
            break;
        }
    }
    if (i == (int)pat.length()) ok = 0;
    return ok;
}

pair<int, int> search(vector<int> &order) {
    int n = txt.length();
    int lo = 0;
    int hi = n - 1;
    while (lo <= hi) {
        int mid = lo + hi >> 1;
        int ok = chk(mid, order);
        if (ok == 0) {
            hi = mid - 1;
        } else if (ok == -1) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    int st = lo;
    hi = n - 1;
    while (lo <= hi) {
        int mid = lo + hi >> 1;
        int ok = chk(mid, order);
        if (ok == 0) {
            lo = mid + 1;
        } else if (ok == -1) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    int en = hi;
    if (st > en) return make_pair(0, -1);
    return make_pair(st, en);
}

void solve() {
    cin >> txt;
    txt += '$';
    vector<int> order = buildSuffixArray();
    int n;
    cin >> n;
    set<int> st;
    while (n--) {
        cin >> pat;
        pair<int, int> ans = search(order);
        for (int i = ans.first; i <= ans.second; i++) {
            st.insert(order[i]);
        }
    }
    for (auto it : st) {
        cout << it << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
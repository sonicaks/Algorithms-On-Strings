#include <bits/stdc++.h>

using namespace std;

int n;
string text;
char ch[4] = {'A', 'C', 'G', 'T'};
vector<int> res;

struct trie {
    struct trie *child[4];
    int end;
};

typedef struct trie trie;

trie *createNode() {
    trie *newNode = new trie;
    for (int i = 0; i < 4; i++) {
        newNode->child[i] = NULL;
    }
    newNode->end = 0;
    return newNode;
}

void insert(trie *root, string s) {
    trie *ptr = root;
    for (int i = 0; i < s.length(); i++) {
        int idx = lower_bound(ch, ch + 4, s[i]) - ch;
        if (ptr->child[idx] == NULL) {
            ptr->child[idx] = createNode();
        }
        ptr = ptr->child[idx];
    }
    ptr->end = 1;
}

void dfs(trie *root, int pos, int start) {
    if (root == NULL) return ;
    if (pos < (int)text.length()) {
        int idx = lower_bound(ch, ch + 4, text[pos]) - ch;
        if (root->child[idx] != NULL) {
            if (root->child[idx]->end == 1) res.push_back(start);
            dfs(root->child[idx], pos + 1, start);
        }
    }
}

void solve() {
    cin >> text;
    cin >> n;
    trie *root = createNode();
    for (int i = 0; i < n; i++) {
        string pat;
        cin >> pat;
        insert(root, pat);
    }
    for (int i = 0; i < text.length(); i++) {
        dfs(root, i, i);
    }
    sort(res.begin(), res.end());
    for (auto i : res) {
        cout << i << " ";
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
#include <bits/stdc++.h>

using namespace std;

int n;
char ch[4] = {'A', 'C', 'G', 'T'};
int cnt = 0;

struct trie {
    struct trie *child[4];
    int num;
};

typedef struct trie trie;

trie *createNode() {
    trie *newNode = new trie;
    for (int i = 0; i < 4; i++) {
        newNode->child[i] = NULL;
    }
    newNode->num = cnt++;
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
}

void dfs(trie *root) {
    if (root == NULL) return ;
    for (int i = 0; i < 4; i++) {
        if (root->child[i] != NULL) {
            cout << root->num << "->" << root->child[i]->num << ":" << ch[i] << "\n";
            dfs(root->child[i]);
        }
    }
}

void solve() {
    cin >> n;
    trie *root = createNode();
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert(root, s);
    }
    dfs(root);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
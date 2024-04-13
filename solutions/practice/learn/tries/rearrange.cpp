#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector

char ord[26];
map<char, int> nodes;

struct node {
    node *children[26]{};
    int paths[26]{};
    int words = 0;

    ~node() { for (auto ch: children) delete ch; }

    void add(string &s, int idx = 0) {
        if (idx == s.size()) return void(words++);

        int i = s[idx] - 'a';
        if (children[i] == nullptr) {
            children[i] = new node();
        }

        children[i]->add(s, idx + 1);
        paths[i]++;
    }

    // print the lexicographically kth string from this point
    void print(int k) {
        if (words >= k) {
            cout << endl;
            return;
        }

        int p = words;
        for (char ch: ord) {
            int i = ch - 'a', c = paths[i];
            if (p + c >= k) {
                // traverse through this path
                cout << ch;
                children[i]->print(k - p);
                return;
            }

            p += c;
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    auto trie = new node();
    rep(i, 0, n) {
        string s;
        cin >> s;
        trie->add(s);
    }

    rep(i, 0, 26) {
        ord[i] = i + 'a';
        nodes[i + 'a'] = i;
    }

    rep(i, 0, q) {
        int t;
        cin >> t;

        string s1, s2;
        char a, b;
        int k;

        switch (t) {
            case 1:
                cin >> s1 >> s2;
                a = s1[0], b = s2[0];
                swap(ord[nodes[a]], ord[nodes[b]]);
                swap(nodes[a], nodes[b]);
                break;

            default:
            case 2:
                cin >> k;
                trie->print(k);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    rep(i, 0, t) {
        cout << "Gift Exchange #" << i + 1 << ":\n";
        solve();
        cout << "\n";
    }

    return 0;
}

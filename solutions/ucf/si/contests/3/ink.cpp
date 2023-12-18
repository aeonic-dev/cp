#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct node {
    node *children[26];
    int paths = 0, words = 0;

    ~node() { for (auto ch: children) delete ch; }

    void add(string &s, int idx = 0) {
        paths++;
        if (idx == s.size()) return void(words++);

        int i = s[idx] - 'a';
        if (children[i] == nullptr) {
            children[i] = new node();
        }

        children[i]->add(s, idx + 1);
    }

    ll sum(int d = 0) {
        ll num = !words ? 0 : d * words * (words - 1) / 2;

        int checked = 0; // number of child paths we've processed
        for (auto ch: children) {
            if (ch == nullptr) continue;

            checked += ch->paths;
            num += d * (paths - checked) * ch->paths;
            num += ch->sum(d + 1);
        }

        return num;
    }
};

void solve() {
    int w;
    cin >> w;

    node *trie = new node();
    rep(i, 0, w) {
        string s;
        cin >> s;

        trie->add(s);
    }

    cout << trie->sum() << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

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
    node *children[26]{};
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

    ll num(string &pfx, int idx = 0) {
        if (idx >= pfx.size()) {
            ll res = words;
            for (auto ch: children) {
                if (ch == nullptr) continue;
                res += ch->num(pfx, idx + 1);
            }
            return res;
        }

        int i = pfx[idx] - 'a';
        if (children[i] == nullptr) return 0;
        return children[i]->num(pfx, idx + 1);
    }
};

void solve() {
    int q;
    cin >> q;

    bool rev = false;
    node *fw = new node();
    node *bw = new node();

    rep(i, 0, q) {
        int t;
        cin >> t;

        string s, r;
        switch (t) {
            case 1: // add participant
                cin >> s;
                r = s; reverse(all(r));
                fw->add(s), bw->add(r);
                break;

            case 2: // # of winners
                cin >> s;
                cout << fw->num(s) << "\n";
                break;

            default:
            case 3: // reverse names
                swap(fw, bw);
                break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    rep(i, 0, t) {
        cout << "Lottery #" << i + 1 << ":\n";
        solve();
        cout << "\n";
    }

    return 0;
}

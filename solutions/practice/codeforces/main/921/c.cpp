#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    node *ch[26];
    int paths = 0;

    ~node() { for (auto child : ch) delete child; }

    void add(char l) {
        for (auto child : ch)
            if (child) child->add(l), paths++;

        if (!ch[l - 'a']) ch[l - 'a'] = new node();
        paths++, ch[l - 'a']->paths++;
    }

    int count_pfx(const string &s, int len) {
        node *cur = this;

        for (int i = 0; i < len; i++) {
//            cout << "i = " << i << '\n';
            if (cur->ch[s[i] - 'a'] == nullptr) return 0;
            cur = cur->ch[s[i] - 'a'];
        }
        return len;
    }
};

void solve() {
    int n, k, m;
    string str;
    cin >> n >> k >> m >> str;

    unique_ptr<node> trie = make_unique<node>();
    rep(i, 0, m) trie->add(str[i]);

    string s(n + 1, '\0');
    rep(len, 1, n + 1) {
        rep(i, 0, k) {
            s[len - 1] = 'a' + i;
//            cout << "len = " << len << ", s = " << s << '\n';
//            cout << "pfx = {" << trie->count_pfx(s, len) << "}\n";
            if (trie->count_pfx(s, len) < len) {
                cout << "NO\n";
                rep(j, 0, len) cout << s[j];
                return void(cout << '\n');
            }
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

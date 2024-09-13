#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, md, hi, sum = 0, lazy = 0, lazy_i;
    node *left = nullptr, *right = nullptr;

    node(int lo, int hi) : lo(lo), md((lo + hi) / 2), hi(hi) {}
    ~node() {
        delete left;
        delete right;
    }

    void incr(int ind, int val) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) return void(sum += val);

        if (lazy) push();
        lazy = val, lazy_i = ind;
    }

    void push() {
        if (lazy_i <= md) {
            if (!left) left = new node(lo, md);
            left->incr(lazy_i, lazy);
        } else {
            if (!right) right = new node(md + 1, hi);
            right->incr(lazy_i, lazy);
        }

        merge();
        lazy = 0;
    }

    ll query(int l, int r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) {
            return sum + lazy;
        }

        if (lazy) push();

        ll res = 0;
        if (left) res += left->query(l, r);
        if (right) res += right->query(l, r);
        return res;
    }

    void merge() {
        sum = (left ? left->sum + left->lazy : 0) +
              (right ? right->sum + right->lazy : 0);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n);
    node *st = new node(1, 1e9);
    rep(i, 0, n) {
        cin >> s[i];
        st->incr(s[i], 1);
    }

    rep(i, 0, m) {
        string q;
        int a, b;
        cin >> q >> a >> b;

        if (q[0] == '!') {
            int old = s[a - 1];
            st->incr(old, -1);
            st->incr(s[a - 1] = b, 1);

            continue;
        }

        cout << st->query(a, b) << "\n";
    }

    delete st;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

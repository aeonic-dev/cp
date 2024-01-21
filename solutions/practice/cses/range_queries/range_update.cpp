#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

vec<ll> s;

struct node {
    int lo, hi;
    ll lazy = 0;
    node *left, *right;

    node(int lo, int hi) : lo(lo), hi(hi) {
        if (lo == hi) return;

        int mid = (lo + hi) / 2;
        left = new node(lo, mid);
        right = new node(mid + 1, hi);
    }

    void incr(int l, int r, ll d) {
        if (r < lo || l > hi) return;
        if (l <= lo && r >= hi) return void(lazy += d);

        left->incr(l, r, d);
        right->incr(l, r, d);
    }

    ll query(int ind) {
        if (ind < lo || ind > hi) return 0;
        if (lo == hi) return s[lo] + lazy;

        if (ind <= (lo + hi) / 2) return left->query(ind) + lazy;
        return right->query(ind) + lazy;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    s = vec<ll>(n);
    rep(i, 0, n) cin >> s[i];

    node *st = new node(0, n - 1);
    rep(i, 0, m) {
        int q, a, b, c;
        cin >> q;

        if (q == 1) {
            cin >> a >> b >> c;
            st->incr(a - 1, b - 1, c);
            continue;
        }

        cin >> a;
        cout << st->query(a - 1) << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

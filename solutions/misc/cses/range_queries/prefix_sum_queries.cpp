#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    ll max, lazy = 0;

    node(int lo, int hi, vec<ll> &pfx) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) {
            max = pfx[lo];
            return;
        }

        left = new node(lo, md, pfx);
        right = new node(md + 1, hi, pfx);
        merge();
    }

    void merge() {
        max = ::max(left->max + left->lazy,
                    right->max + right->lazy);
    }

    void add(int l, int r, int d) {
        if (r < lo || l > hi) return;
        if (l <= lo && r >= hi) {
            lazy += d;
            return;
        }

        left->add(l, r, d);
        right->add(l, r, d);
        merge();
    }

    ll query(int l, int r) {
        if (r < lo || l > hi) return LLONG_MIN;
        if (l <= lo && r >= hi) return max + lazy;

        return ::max(left->query(l, r),
                     right->query(l, r)) + lazy;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vec<int> s(n);
    vec<ll> pfx(n + 1, 0);
    rep(i, 0, n) {
        cin >> s[i];
        pfx[i + 1] = pfx[i] + s[i];
    }

    auto st = new node(0, n, pfx);
    rep(i, 0, m) {
        int q, a, b;
        cin >> q >> a >> b;

        if (q == 1) {
            int d = b - s[a - 1];
            s[a - 1] = b;
            st->add(a, n, d);

            continue;
        }

        ll res = st->query(a, b) - st->query(a - 1, a - 1);
        cout << ::max(res, 0ll) << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

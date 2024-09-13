#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    ll sum, max_sum, pfx_max, pfx_len, sfx_max, sfx_len;

    node(int lo, int hi, vec<int> &s) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) {
            sum = max_sum = pfx_max = sfx_max = s[lo];
            pfx_len = sfx_len = 1;
            return;
        }

        left = new node(lo, md, s);
        right = new node(md + 1, hi, s);
        merge();
    }

    void merge() {
        if (left->pfx_len == md - lo + 1 && right->pfx_max > 0) {
            pfx_max = left->pfx_max + right->pfx_max;
            pfx_len = left->pfx_len + right->pfx_len;
        } else {
            pfx_max = left->pfx_max;
            pfx_len = left->pfx_len;
        }

        if (left->sum + right->pfx_max >= pfx_max) {
            pfx_max = left->sum + right->pfx_max;
            pfx_len = (md - lo + 1) + right->pfx_len;
        }

        if (right->sfx_len == hi - md && left->sfx_max > 0) {
            sfx_max = left->sfx_max + right->sfx_max;
            sfx_len = left->sfx_len + right->sfx_len;
        } else {
            sfx_max = right->sfx_max;
            sfx_len = right->sfx_len;
        }

        if (left->sfx_max + right->sum >= sfx_max) {
            sfx_max = left->sfx_max + right->sum;
            sfx_len = (hi - md) + left->sfx_len;
        }

        sum = left->sum + right->sum;
        max_sum = max({
                              // full sum and max pfx/sfx
                              sum, pfx_max, sfx_max,
                              // best of both sides
                              left->max_sum, right->max_sum,
                              // pfx/sfx, middle region
                              left->sfx_max, right->pfx_max,
                              left->sfx_max + right->pfx_max,
                              // empty subarray
                              0ll});
    }

    void update(int ind, int val) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) {
            sum = max_sum = pfx_max = sfx_max = val;
            return;
        }

        left->update(ind, val);
        right->update(ind, val);
        merge();
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];
    node *st = new node(0, n - 1, s);

    rep(i, 0, m) {
        int ind, val;
        cin >> ind >> val;

        st->update(ind - 1, val);
        cout << max(st->max_sum, 0ll) << "\n";
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

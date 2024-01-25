#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    ll minl, minr; // cost incl delivery

    node(int lo, int hi, vec<int> &p) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) {
            minl = minr = p[lo];
            return;
        }

        left = new node(lo, md, p);
        right = new node(md + 1, hi, p);
        merge();
    }

    void merge() {
        minl = min(left->minl, right->minl + (md - lo + 1));
        minr = min(right->minr, left->minr + (hi - md));
    }

    void update(int ind, int val) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) return void(minl = minr = val);

        left->update(ind, val);
        right->update(ind, val);
        merge();
    }

    ll query(int ind) {
        if (ind < lo) return minl + (lo - ind);
        if (ind > hi) return minr + (ind - hi);

        // leaf minl = minr
        if (lo == hi) return minr;

        if (ind <= md) return min(left->query(ind), right->minl + (md - ind + 1));
        return min(left->minr + (ind - md), right->query(ind));
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n + 1);
    rep(i, 0, n) cin >> s[i + 1];
    node *st = new node(1, n, s);

    rep(i, 0, m) {
        int q, a, b;
        cin >> q;

        if (q == 1) {
            cin >> a >> b;
            st->update(a, b);
        } else {
            cin >> a;
            cout << st->query(a) << "\n";
        }
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

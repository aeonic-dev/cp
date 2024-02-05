#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    int max;

    node(int lo, int hi, vec<int> &s) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) {
            max = s[lo - 1];
            return;
        }

        left = new node(lo, md, s);
        right = new node(md + 1, hi, s);
        merge();
    }

    void merge() {
        max = ::max(left->max, right->max);
    }

    void update(int i, int d) {
        if (i < lo || i > hi) return;
        if (lo == hi) return void(max += d);

        left->update(i, d);
        right->update(i, d);
        merge();
    }

    int query(int v) {
        if (v > max) return 0;
        if (lo == hi) return lo;
        if (v <= left->max) return left->query(v);
        return right->query(v);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];

    node *st = new node(1, n, s);
    rep(i, 0, m) {
        int v;
        cin >> v;

        int ind = st->query(v);
        if (ind == 0) {
            cout << "0 ";
            continue;
        }

        cout << ind << " ";
        st->update(ind, -v);
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

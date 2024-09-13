#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

vec<int> s;

struct node {
    int lo, hi, val;
    node *left, *right;

    node(int lo, int hi) : lo(lo), hi(hi) {
        if (lo == hi) {
            val = s[lo];
            return;
        }

        int mid = (lo + hi) / 2;
        left = new node(lo, mid);
        right = new node(mid + 1, hi);
        merge();
    }

    void merge() {
        val = left->val ^ right->val;
    }

    int query(int l, int r) {
        if (l > hi || r < lo) return 0;
        if (l <= lo && r >= hi) return val;

        return left->query(l, r) ^ right->query(l, r);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    s = vec<int>(n);
    rep(i, 0, n) cin >> s[i];

    node *st = new node(0, n - 1);
    rep(i, 0, q) {
        int a, b;
        cin >> a >> b;

        cout << st->query(a - 1, b - 1) << "\n";
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

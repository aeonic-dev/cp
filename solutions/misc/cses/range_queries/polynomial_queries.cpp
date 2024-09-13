#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    ll sum, lazy_coeff = 0, lazy_const = 0;

    node(int lo, int hi, vec<int> &s) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) {
            sum = s[lo - 1];
            return;
        }

        left = new node(lo, md, s);
        right = new node(md + 1, hi, s);
        merge();
    }

    void merge() {
        sum = left->get_sum() + right->get_sum();
    }

    ll get_sum() {
        return sum
               + lazy_coeff * (hi - lo + 1) * (hi + lo) / 2
               + lazy_const * (hi - lo + 1);
    }

    void push() {
        left->add(lo, hi, lazy_coeff, lazy_const);
        right->add(lo, hi, lazy_coeff, lazy_const);
        merge(), lazy_coeff = lazy_const = 0;
    }

    void add(int l, int r, ll b, ll c) {
        if (r < lo || l > hi) return;
        if (l <= lo && r >= hi) {
            lazy_coeff += b, lazy_const += c;
            return;
        }

        if (lazy_coeff) push();
        left->add(l, r, b, c);
        right->add(l, r, b, c);
        merge();
    }

    ll query(int l, int r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) return get_sum();

        if (lazy_coeff) push();
        return left->query(l, r) + right->query(l, r);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];
    node *st = new node(1, n, s);

    rep(i, 0, m) {
        int q, a, b;
        cin >> q >> a >> b;

        if (q == 1) {
            st->add(a, b, 1, 1 - a);
            continue;
        }

        cout << st->query(a, b) << "\n";
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

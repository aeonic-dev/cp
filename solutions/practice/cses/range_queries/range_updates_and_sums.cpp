#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    ll sum, lazy_add = 0, lazy_set = 0;

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
        sum = left->full_sum() + right->full_sum();
    }

    void push() {
        if (lazy_set) {
            left->set(lo, hi, lazy_set + lazy_add);
            right->set(lo, hi, lazy_set + lazy_add);
            merge(), lazy_add = lazy_set = 0;
            return;
        }

        left->add(lo, hi, lazy_add);
        right->add(lo, hi, lazy_add);
        merge(), lazy_add = 0;
    }

    void add(int l, int r, ll d) {
        if (r < lo || l > hi) return;
        if (lo == hi) return void(sum += d);

        if (l <= lo && r >= hi) {
            lazy_add += d;
            return;
        }

        if (lazy_add || lazy_set) push();
        left->add(l, r, d);
        right->add(l, r, d);
        merge();
    }

    void set(int l, int r, ll v) {
        if (r < lo || l > hi) return;
        if (lo == hi) return void(sum = v);

        if (l <= lo && r >= hi) {
            lazy_add = 0, lazy_set = v;
            return;
        }

        if (lazy_add || lazy_set) push();
        left->set(l, r, v);
        right->set(l, r, v);
        merge();
    }

    ll full_sum() {
        if (lazy_set) return (lazy_set + lazy_add) * (hi - lo + 1);
        return sum + lazy_add * (hi - lo + 1);
    }

    ll query(int l, int r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) return full_sum();

        if (lazy_add || lazy_set) push();
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
        int q, a, b, x;
        cin >> q >> a >> b;

        switch (q) {
            case 1:
                cin >> x;
                st->add(a, b, x);
                break;

            case 2:
                cin >> x;
                st->set(a, b, x);
                break;

            case 3:
                cout << st->query(a, b) << "\n";
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

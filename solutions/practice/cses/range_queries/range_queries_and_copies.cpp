#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;
typedef unsigned long long ull;

vec<ull> t;

struct node {
    int lo, hi;
    node *left, *right;
    ull sum;

    node(int lo, int hi) : lo(lo), hi(hi) {}

    void set(int ind, int val) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) return void(sum = val);

        if (ind <= left->hi) {
            node *old = left;
            left = old->copy();
            left->set(ind, val);
            merge();

            return;
        }

        node *old = right;
        right = old->copy();
        right->set(ind, val);
        merge();
    }

    ull query(int l, int r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) return sum;

        return left->query(l, r) + right->query(l, r);
    }

    node *copy() {
        node *res = new node(lo, hi);
        res->copy_from(this);
        return res;
    }

    void init() {
        if (lo == hi) {
            sum = t[lo];
            return;
        }

        left = new node(lo, (lo + hi) / 2), left->init();
        right = new node((lo + hi) / 2 + 1, hi), right->init();
        merge();
    }

private:
    void copy_from(node *old) {
        left = old->left;
        right = old->right;
        sum = old->sum;
    }

    void merge() {
        sum = left->sum + right->sum;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    t = vec<ull>(n);
    rep(i, 0, n) cin >> t[i];
    vec<node *> sts{new node(0, n - 1)};
    sts[0]->init();

    rep(i, 0, m) {
        int q, a, b, c;
        cin >> q;

        switch (q) {
            case 1:
                cin >> a >> b >> c;
                sts[a - 1]->set(b - 1, c);
                break;

            case 2:
                cin >> a >> b >> c;
                cout << sts[a - 1]->query(b - 1, c - 1) << "\n";
                break;

            default:
            case 3:
                cin >> a;
                sts.push_back(sts[a - 1]->copy());
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc = 1;
//    cin >> t;
    while (tc--) solve();

    return 0;
}

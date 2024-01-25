#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    int sum = 0;

    node(int lo, int hi) : lo(lo), hi(hi), md((lo + hi) / 2) {}

    void init() {
        if (lo == hi) return;

        left = new node(lo, md);
        right = new node(md + 1, hi);
        left->init(), right->init();
    }

    void merge() { sum = left->sum + right->sum; }

    node *copy() {
        node *res = new node(lo, hi);
        res->left = left, res->right = right;
        res->sum = sum;

        return res;
    }

    node *update(int i, int d) {
        if (i < lo || i > hi) return this;
        if (lo == hi) {
            node *res = copy();
            res->sum += d;
            return res;
        }

        node *res = copy();
        res->left = left->update(i, d);
        res->right = right->update(i, d);

        return res->merge(), res;
    }

    int query(int l, int r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) return sum;

        return left->query(l, r) + right->query(l, r);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n);
    vec<pair<int, int>> ind(n);
    rep(i, 0, n) {
        cin >> s[i];
        ind[i] = {s[i], 1};
    }

    vec<node *> p(n + 1);
    p[0] = new node(1, n + 1);
    p[0]->init();

    sort(all(ind));
    rep(i, 0, n) {
        int v = s[i];
        auto &at = *lower_bound(all(ind), pair<int, int>{v, 0});
        p[i + 1] = p[i]->update(at.second, 1);
        at.second = i + 2;
    }

    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;

        int res = p[b]->query(1, a) -
                  p[a - 1]->query(1, a);
        cout << res << "\n";
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

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md;
    node *left, *right;
    ll sum, lazy_set = 0;

    node(int lo, int hi) : lo(lo), hi(hi), md((lo + hi) / 2) {}

    void init(const vec<int> &s) {
        if (lo == hi) return void(sum = s[lo]);

        left = new node(lo, md), left->init(s);
        right = new node(md + 1, hi), right->init(s);
        merge();
    }

    void merge() { sum = left->fsum() + right->fsum(); }
    ll fsum() const { return lazy_set ? lazy_set * (hi - lo + 1) : sum; }

    node *copy() {
        node *ret = new node(lo, hi);
        ret->sum = sum, ret->lazy_set = lazy_set;

        return ret;
    }

    node *set(int l, int r, int v) {
        if (r < lo || l > hi) return this;
        if (l <= lo && r >= hi) {
            node *ret = copy();
            return ret->lazy_set = v, ret;
        }

        node *ret = copy();
        ret->left = left->set(l, r, v);
        ret->right = right->set(l, r, v);
        ret->merge();

        return ret;
    }

    ll query(int l, int r, int d = 0) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) return fsum();

        if (lazy_set) return lazy_set * (min(r, hi) - max(l, lo) + 1);
        return left->query(l, r, d + 1) + right->query(l, r, d + 1);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n);
    vec<ll> pfx(n + 1, 0);
    rep(i, 0, n) {
        cin >> s[i];
        pfx[i + 1] = s[i] + pfx[i];
    }

    // PST roots paired with the earliest-index update they include
    vec<pair<int, node *>> pst{{n, new node(0, n - 1)}};
    pst[0].second->init(s);

    vec<pair<int, int>> mt; // running max tail {max, ind}
    for (int i = n - 1; i >= 0; i--) {
        // if the stack is empty, we'll update a range to the end of the array
        int j = n;

        // otherwise search for the index the range ends at
        if (!mt.empty()) {
            int lo = 0, hi = mt.size() - 1;
            while (lo <= hi) {
                int md = (lo + hi) / 2;
                // find the first index j > i with s[j] >= s[i]
                if (mt[md].first >= s[i]) j = mt[md].second, lo = md + 1;
                else hi = md - 1;
            }
        }

        // update the stack after we find j
        while (!mt.empty() && mt.back().first <= s[i]) mt.pop_back();
        mt.emplace_back(s[i], i);

        // if no values would be affected by this max (empty range), do nothing
        if (j - i <= 1) continue;

        // otherwise we have a range that will need to be increased to match this max.
        // we range set on a new copy of the segment tree to reflect the moves in the range (i, j)
        pst.emplace_back(i, pst.back().second->set(i + 1, j - 1, s[i]));
    }

    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        int at = 0, lo = 0, hi = pst.size() - 1;
        while (lo <= hi) {
            int md = (lo + hi) / 2;
            if (pst[md].first >= a) at = md, lo = md + 1;
            else hi = md - 1;
        }

        ll res = pst[at].second->query(a, b);
        ll sum = pfx[b + 1] - pfx[a];
        cout << res - sum << "\n";
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

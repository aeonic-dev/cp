#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

struct node {
    node *left = nullptr, *rght = nullptr;
    ll lo, hi, md;
    ll num = 0, flip = 0;

    node(ll lo, ll hi) : lo(lo), hi(hi), md((lo + hi) / 2) {}
    ~node() { delete left, delete rght; }

    node *getl() { return left ? left : left = new node(lo, md); }
    node *getr() { return rght ? rght : rght = new node(md + 1, hi); }

    ll get_num(ll l, ll r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi)
            return flip ? hi - lo + 1 - num : num;

        push();
        return getl()->get_num(l, r) + getr()->get_num(l, r);
    }

    void do_flip(ll l, ll r) {
        if (r < lo || l > hi) return;
        if (l <= lo && r >= hi) {
            flip ^= 1;
            return;
        }

        push();
        getl()->do_flip(l, r);
        getr()->do_flip(l, r);
        num = getl()->get_num(lo, hi)
              + getr()->get_num(lo, hi);
    }

    void push() {
        if (flip) {
            num = hi - lo + 1 - num;
            if (lo != hi) {
                getl()->do_flip(lo, hi);
                getr()->do_flip(lo, hi);
            }
            flip = 0;
        }
    }
};

void solve() {
    ll n, x1, x2, y1, y2;
    cin >> n;

    multiset<tuple<ll, ll, ll>> evts; // y, [l, r]
    rep(i, 0, n) {
        cin >> x1 >> y1 >> x2 >> y2;
        evts.emplace(y1, x1, --x2);
        evts.emplace(y2, x1, x2);
    }

    ll res = 0, prev_y = -1;
    node st(0, 1e9);
    for (auto [y, l, r] : evts) {
        if (prev_y != -1) {
            res += (y - prev_y) * st.get_num(0, 1e9);
        }
        st.do_flip(l, r);
        prev_y = y;
    }
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

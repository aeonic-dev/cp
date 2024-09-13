#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct node {
    int lo, hi, md, bits;
    node *left, *right;

    node(int lo, int hi) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) {
            bits = 1;
            return;
        }

        left = new node(lo, md);
        right = new node(md + 1, hi);
        merge();
    }

    void merge() {
        bits = left->bits + right->bits;
    }

    void set(int ind, int val) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) return void(bits = val);

        left->set(ind, val);
        right->set(ind, val);
        merge();
    }

    int kth(int k) const {
        if (lo == hi) return lo;
        if (k <= left->bits) return left->kth(k);
        return right->kth(k - left->bits);
    }
};

void solve() {
    int n;
    cin >> n;
    vec<int> s(n);
    rep(i, 0, n) cin >> s[i];

    node *st = new node(1, n);
    rep(i, 0, n) {
        int k;
        cin >> k;

        int ind = st->kth(k);
        st->set(ind, 0);

        cout << s[ind - 1] << " ";
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

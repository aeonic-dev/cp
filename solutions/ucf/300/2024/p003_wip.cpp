#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

typedef bitset<20> B;
const ld eps = 1e-8;

ld go(B &bs, const vector<ld> &ps) {
    if (bs.none()) return 0.l;

    ld res = 0;
    rep(i, 0, sz(ps)) {
        if (!bs[i]) continue;
        ld p0 = 1 - ps[i], p1 = ps[i];
        ld p_a0 = 1, p_a1 = 1;
        rep(j, 0, sz(ps)) {
            if (j == i || !bs[j]) continue;
            p_a0 *= 1 - ps[j], p_a1 *= ps[j];
        }

        int r;
        ld p;
        for (r = 1, p = p0 * p_a0; p > eps; r++, p *= p0 * p_a0) ; // wait what the fuck
        // res += 
    }
}

void solve() {
    int n;
    cin >> n;
    vector<ld> ps(n);
    for (ld &p : ps) cin >> p;

    B bs;
    ld res = go(bs, ps);
    cout << setprecision(8) << fixed << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

int logb(int a, int b) {
    return log2(a) / log2(b);
}

void solve() {
    ll a, b, l;
    cin >> a >> b >> l;

    const int MAXP = 21;
    int mpa = MAXP, mpb = MAXP;
    vector<ll> pa(MAXP, 1), pb(MAXP, 1);
    rep(i, 1, MAXP) {
        pa[i] = pa[i - 1] * a;
        pb[i] = pb[i - 1] * b;
        if (pa[i] <= 0) mpa = i;
        if (pb[i] <= 0) mpb = i;
    }

    set<ll> ks;
    rep(x, 0, min(logb(l, a) + 1, mpa)) {
        if (l % pa[x]) continue;
        rep(y, 0, min(logb(l / pa[x], b) + 1, mpb)) {
            if (l % (pa[x] * pb[y])) continue;
            ks.insert(l / (pa[x] * pb[y]));
        }
    }
    cout << ks.size() << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

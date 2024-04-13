#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;
    vi a(n), pfx(n + 1, 0);
    rep(i, 0, n) {
        cin >> a[i];
        pfx[i + 1] = pfx[i] + a[i];
    }

    int q, l;
    ll u;
    cin >> q;
    rep(i, 0, q) {
        cin >> l >> u, l--;

        int lo = l, hi = n - 1;
        while (lo <= hi) {
            int m1 = lo + (hi - lo) / 3;
            int m2 = hi - (hi - lo) / 3;

            ll n1 = pfx[m1 + 1] - pfx[l];
            ll n2 = pfx[m2 + 1] - pfx[l];
            ll s1 = n1 * u - n1 * (n1 - 1) / 2;
            ll s2 = n2 * u - n2 * (n2 - 1) / 2;
//            cout << "m1 = " << m1 << ", n1 = " << n1 << " -> " << s1 << "\n";
//            cout << "m2 = " << m2 << ", n2 = " << n2 << " -> " << s2 << "\n";

            if (s1 < s2) lo = m1 + 1;
            else hi = m2 - 1;
        }
        cout << lo + 1 << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

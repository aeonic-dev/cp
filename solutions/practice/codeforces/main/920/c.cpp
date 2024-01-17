#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    ll n, f, a, b;
    cin >> n >> f >> a >> b;

    vec<ll> m(n + 1, 0);
    rep(i, 0, n) cin >> m[i + 1];
    sort(all(m));

    ll bat = f;
    rep(i, 0, n + 1) {
        ll mi = m[i];
        if (i < n) {
            ll cost = min(b, a * (m[i + 1] - mi));
            bat -= cost;
        }

        if (bat <= 0) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

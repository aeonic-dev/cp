#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, q, s, d, k;
    cin >> n >> q;

    vec<ll> a(n), pfx(n + 1, 0);
    rep(i, 0, n) {
        cin >> a[i];
        pfx[i + 1] = pfx[i] + a[i];
    }

    rep(i, 0, q) {
        cin >> s >> d >> k;
        s--;

        ll sum = 0;
        rep(j, 0, k) {
            sum += pfx[s + d * (k - 1) + 1] - pfx[s + d * j];
            if (j < k - 1)
                sum -= (pfx[s + d * (j + 1)] - pfx[s + d * j + 1]) * (j + 1);
        }
        cout << sum << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n;
    cin >> n;
    vec<ll> a(n), f(n + 1, 0), pfx(n + 2, 0);
    rep(i, 0, n) {
        cin >> a[i];
        f[a[i]]++;
    }

    rep(i, 0, n + 1) {
        pfx[i + 1] = pfx[i] + f[i];
    }

    ll num = 0;
    for (int i = n; i >= 0; i--) {
        if (f[i] >= 3) num += (f[i] * (f[i] - 1) * (f[i] - 2)) / 6;
        if (i > 0 && f[i] >= 2) {
            num += f[i] * (f[i] - 1) / 2 * (pfx[i]);
        }
    }

    cout << num << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

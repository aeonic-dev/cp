#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    ll x, n;
    cin >> x >> n;

    ll res = 1;
    for (ll d = 1; d * d <= x; d++) {
        if (x % d) continue;

        if (n * d <= x) res = max(res, d);
        if (n <= d) res = max(res, x / d);
    }
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n;
    cin >> n;
    vec<int> a(n);
    rep(i, 0, n) cin >> a[i];

    vec<ll> pfx_ltor(n + 1, 0), pfx_rtol(n + 1, 0);
    rep(i, 0, n - 1) {
        int ltor = abs(a[i + 1] - a[i]);
        if (i == 0 || ltor < abs(a[i - 1] - a[i])) ltor = 1;
        pfx_ltor[i + 1] = pfx_ltor[i] + ltor;

        int rtol = abs(a[n - 2 - i] - a[n - 1 - i]);
        if (i == 0 || rtol < abs(a[n - i] - a[n - 1 - i])) rtol = 1;
        pfx_rtol[i + 1] = pfx_rtol[i] + rtol;
    }

    int m;
    cin >> m;
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;

        if (u < v) cout << pfx_ltor[v - 1] - pfx_ltor[u - 1] << "\n";
        else cout << pfx_rtol[n - v] - pfx_rtol[n - u] << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

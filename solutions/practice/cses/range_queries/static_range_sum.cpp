#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, q;
    cin >> n >> q;
    vec<ll> s(n), pfx(n + 1, 0);
    rep(i, 0, n) {
        cin >> s[i];
        pfx[i + 1] = pfx[i] + s[i];
    }

    rep(i, 0, q) {
        int a, b;
        cin >> a >> b;
        cout << pfx[b] - pfx[a - 1] << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

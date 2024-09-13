#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

const ll base = 30;
const ll mod = 1e9 + 7;

void solve() {
    string s;
    cin >> s;

    size_t n = s.size();
    vec<ll> pwr(n + 1, 1), pfx(n + 1, 0);
    rep(i, 0, n) {
        pwr[i + 1] = (pwr[i] * base) % mod;
        pfx[i + 1] = (pfx[i] * base) % mod + (s[i] - 'a' + 1);
        pfx[i + 1] %= mod;
    }

    rep(len, 1, n) {
        ll hp = pfx[len];
        ll hs = (pfx[n] - (pfx[n - len] * pwr[len]) % mod + mod) % mod;
        if (hp == hs) cout << len << " ";
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

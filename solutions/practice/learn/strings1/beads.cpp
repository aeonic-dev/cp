#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll base = 30;
const ll mod = 1e9 + 7;

ll hash_from(const vec<ll> &pfx, vec<ll> &pwr, int n, int i) {
    ll fr = (pfx[n] + mod - (pfx[i] * pwr[n - i]) % mod) % mod;
    return ((fr * pwr[i]) % mod + pfx[i]) % mod;
}

int tc = 0;
void solve() {
    cout << "Case #" << ++tc << ": ";

    string a, b;
    cin >> a >> b;
    if (a.size() != b.size()) {
        cout << "NO\n";
        return;
    }

    int n = a.size();
    vec<ll> pwr(n + 1, 1),
            pfxfr(n + 1, 0), pfxbk(n + 1, 0);
    ll hb = 0;
    rep(i, 0, n) {
        pwr[i + 1] = (pwr[i] * base) % mod;
        pfxfr[i + 1] = ((pfxfr[i] * base) % mod + (a[i] - 'a' + 1)) % mod;
        pfxbk[i + 1] = ((pfxbk[i] * base) % mod + (a[n - i - 1] - 'a' + 1)) % mod;
        hb = ((hb * base) % mod + (b[i] - 'a' + 1)) % mod;
    }

    rep(i, 0, n) {
        ll hfr = hash_from(pfxfr, pwr, n, i);
        ll hbk = hash_from(pfxbk, pwr, n, i);
        if (hfr == hb || hbk == hb) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
}

int main() {
//    cin.tie(0)->sync_with_stdio(0);
//    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll mod = 1e9 + 7;
void solve() {
    int n, k;
    cin >> n >> k;
    vll a(n);
    rep(i, 0, n) cin >> a[i];

    ll max = 0, min = 0, sum = 0;
    rep(i, 0, n) {
        sum = sum + a[i];
        ll cur = sum - min;

        max = ::max({max, cur, 0ll});
        min = ::min(min, sum);
    }

    ll res = sum, mul = 1;
    rep(i, 1, k + 1) {
        res += mul * ((max + mod) % mod) % mod + mod;
        res %= mod;
        mul = (mul * 2) % mod;
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

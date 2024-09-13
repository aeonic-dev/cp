#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll rot = 360'000;
const ll mod = 1e9 + 7, base = 360'001;
void solve() {
    int n;
    cin >> n;
    vll a(n), b(n), s_a(n), s_b(n), pwr(n + 1, 1);
    rep(i, 0, n) pwr[i + 1] = (pwr[i] * base) % mod;
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];
    sort(all(a));
    sort(all(b));
    rep(i, 0, n) s_a[i] = (a[i] - a[(i - 1 + n) % n] + rot) % rot;
    rep(i, 0, n) s_b[i] = (b[i] - b[(i - 1 + n) % n] + rot) % rot;
    ll hash_b = 0;
    rep(i, 0, n) {
        hash_b = (hash_b * base) % mod;
        hash_b = (hash_b + s_b[i] + 1) % mod;
    }
    vll pfx(n + 1);
    rep(i, 0, n) {
        pfx[i + 1] = ((pfx[i] * base) % mod + s_a[i] + 1) % mod;
    }
    
    rep(st, 0, n) {
        ll hash = (pfx[n] - (pfx[st] * pwr[n - st]) % mod + mod) % mod;
        hash = ((hash * pwr[st]) % mod + pfx[st]) % mod;
        if (hash == hash_b) return void(cout << "possible\n");
    }
    cout << "impossible\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

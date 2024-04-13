#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int mod = 1e9 + 7; /**< must be prime */
vector<long long> inv(2, 1), fact(2, 1), inv_fact(2, 1);
/**
 * @param n,k integers with n < mod
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
//NOLINTNEXTLINE(readability-identifier-naming)
inline long long C(int n, int k) {
    assert(n < mod);
    if (k < 0 || n < k) return 0;
    while (sz(inv) <= n) {
        int i = sz(inv);
        inv.push_back(mod - (mod / i) * inv[mod % i] % mod);
        fact.push_back(i * fact[i - 1] % mod);
        inv_fact.push_back(inv[i] * inv_fact[i - 1] % mod);
    }
    return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}

void solve() {
    int n, k;
    string str;
    cin >> n >> k >> str;
    
    vector<vi> f(k, vi(26, 0));
    rep(i, 0, n) {
        f[i % k][str[i] - 'a']++;
    }
    
    ll res = 1;
    rep(i, 0, k) {
        int num = accumulate(all(f[i]), 0);
        for (int v : f[i]) {
            if (v < 1) continue;
            res *= C(num, v), res %= mod;
            num -= v;
        }
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

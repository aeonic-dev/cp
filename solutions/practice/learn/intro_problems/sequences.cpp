#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, k;
    cin >> n >> k;
    vll s(n);
    rep(i, 0, n) cin >> s[i];
    rep(_, 0, k) {
        vll ns;
        rep(i, 1, sz(s)) ns.push_back(s[i - 1] + s[i]);
        s = ns;
    }
    for (ll x : s) cout << x << " ";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}

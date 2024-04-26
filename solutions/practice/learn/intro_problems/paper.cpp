#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, s, p;
    cin >> n;
    
    ll res = 0;
    rep(i, 0, n) {
        cin >> s >> p;
        ll num = p / 4 + (p % 4 != 0);
        res += num * s;
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

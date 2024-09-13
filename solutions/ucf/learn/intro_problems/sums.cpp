#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve(int tc) {
    int n;
    cin >> n;
    
    ll sum = 0;
    rep(k, 1, n + 1) {
        sum += (ll) k * (k + 1) * (k + 2) / 2;
    }
    cout << tc << " " << n << " " << sum << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    rep(tc, 1, t + 1) solve(tc);
    
    return 0;
}

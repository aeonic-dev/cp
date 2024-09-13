#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    ll n;
    cin >> n;
    
    ll res = 1;
    while (res * 2 - 1 <= n) res *= 2;
    res--;
    
    ll num = 1, x = res;
    while (x > 1) num++, x /= 2;
    cout << num << " " << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}

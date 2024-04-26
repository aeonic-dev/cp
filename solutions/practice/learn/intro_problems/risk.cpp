#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, tmp;
    cin >> n;
    
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    
    multiset<int> b;
    rep(i, 0, n) {
        cin >> tmp;
        b.insert(tmp);
    }
    
    int res = 0;
    for (int v : a) {
        auto it = b.lower_bound(v);
        if (it == b.end()) break;
        res++;
        b.erase(it);
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

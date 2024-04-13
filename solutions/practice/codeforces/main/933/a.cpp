#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vi b(n), c(m);
    rep(i, 0, n) cin >> b[i];
    rep(i, 0, m) cin >> c[i];

    int res = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            int sum = b[i] + c[j];
            if (sum <= k) res++;
        }
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

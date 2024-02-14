#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;

    vec<int> s(n);
    map<pair<int, int>, int> f;
    ll num = 0;
    rep(i, 0, n) {
        cin >> s[i];
        int mx = s[i] % x, my = s[i] % y;
        int nx = (x - mx) % x, ny = my;

        num += f[{nx, ny}];
        f[{mx, my}]++;
    }
    cout << num << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;

    const int maxlog = 30; // log2(1e9)
    vec<vec<int>> par(maxlog, vec<int>(n));
    rep(i, 0, n) cin >> par[0][i], par[0][i]--;
    rep(j, 1, maxlog) {
        rep(i, 0, n) par[j][i] = par[j - 1][par[j - 1][i]];
    }

    rep(i, 0, m) {
        int cur, k;
        cin >> cur >> k, cur--;
        if (k == 0) {
            cout << cur + 1 << '\n';
            continue;
        }

        int l = __builtin_ctz(k);
        int r = sizeof(int) * CHAR_BIT - __builtin_clz(k); // exclusive
        rep(j, l, r) {
            if (par[0][cur] == cur) break;
            if ((1 << j) & k) cur = par[j][cur];
        }
        cout << cur + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

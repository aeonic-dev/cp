#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> s(n), ind(n + 1);
    rep(i, 0, n) cin >> s[i], ind[s[i]] = i;

    auto chk = [&](int val) {
        if (val < 1 || val >= n) return false;
        return ind[val] > ind[val + 1];
    };

    int res = 1;
    rep(i, 1, n) res += chk(i);

    rep(q, 0, m) {
        int a, b;
        cin >> a >> b, a--, b--;
        int u = s[a], v = s[b];

        int sub = chk(u) + chk(v);
        if (u - 1 != v) sub += chk(u - 1);
        if (v - 1 != u) sub += chk(v - 1);

        swap(s[a], s[b]);
        swap(ind[u], ind[v]);

        res -= sub;
        res += chk(u) + chk(v);
        if (u - 1 != v) res += chk(u - 1);
        if (v - 1 != u) res += chk(v - 1);
        cout << res << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

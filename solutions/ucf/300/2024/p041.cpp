#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n;
    cin >> n;

    // f, cost, mkt price, stock, profit
    // p[i] = max profit from buying some j such that f[j] = i
    vi f(n), c(n), m(n), s(n), p(n, 0);
    vector<vi> par(n); // nodes such that f[node] = i, sorted by profit
    rep(i, 0, n) cin >> f[i] >> c[i] >> m[i] >> s[i], f[i]--;
    rep(i, 0, n) {
        // if i is in stock, it might make a better profit than f[i]'s current best
        if (!s[i]) continue;
        par[f[i]].push_back(i);
        // p[f[i]] = max(p[f[i]], m[f[i]] - c[i]);
    }
    rep(i, 0, n) {
        sort(all(par[i]), [&](int a, int b) { return m[i] - c[a] > m[i] - c[b]; });
        p[i] = par[i].empty() ? 0 : max(0, m[i] - c[par[i][0]]);
    }

    // we can always buy everything down to 1 left
    ll res = 0;
    rep(i, 0, n) {
        if (p[i] <= 0 || s[i] <= 1) continue;
        res += (ll) p[i] * (s[i] - 1);
    }

    // now enumerate cycles; we can buy all but the least profitable
    bitset<100'000> vis;
    rep(i, 0, n) {
        if (vis[i] || !s[i] || !p[i]) continue;

        vi cyc;
        int last = -1;
        for (int j = i; !vis[j]; j = f[j]) {
            vis[j] = 1;
            if (!s[j]
                || p[j] <= 0
                || (last != -1 && last != par[j][0])) continue;
            cyc.push_back(last = j);
        }
        if (sz(cyc) <= 1 || f[cyc.back()] != cyc.front()) {
            for (int j : cyc)
                if (s[j] && p[j] > 0) res += p[j], s[j] = 0;
            continue;
        }

        ll sum = 0, sub = INT_MAX;
        for (int j : cyc) {
            ll cur_sub = sz(par[f[j]]) > 1
                                 ? c[par[f[j]][1]] - c[par[f[j]][0]]
                                 : p[j];
            sum += p[j];
            sub = min(sub, cur_sub);
        }
        cout << "sum = " << sum << ", sub = " << sub << '\n';
        res += sum - sub;
    }
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

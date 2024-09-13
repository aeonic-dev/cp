#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct dsu {
    vector<int> par, siz;
    int comp, maxc;
    dsu(int n) : par(n, 1), siz(n, 1), comp(n), maxc(1) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int a) {
        if (par[a] != a) par[a] = find(par[a]);
        return par[a];
    }
    pair<int, int> join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return {comp, maxc};
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
        return {--comp, maxc = max(maxc, siz[a])};
    }
    bool connected() {
        rep(i, 1, par.size()) {
            if (find(i) != find(i - 1)) return false;
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    dsu ds(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        auto [num, max] = ds.join(u - 1, v - 1);
        cout << num << ' ' << max << '\n';
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

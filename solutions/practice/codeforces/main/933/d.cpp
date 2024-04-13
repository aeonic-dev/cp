#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n, m, st;
    cin >> n >> m >> st;
    st--;

    vector<pair<int, int>> moves(m);
    rep(i, 0, m) {
        string s;
        cin >> moves[i].first >> s;
        moves[i].second = (s[0] == '?') ? 0 : (s[0] == '0' ? 1 : -1);
    }

    set<int> res;
    vector<bitset<1000>> vis(1000);
    auto dfs = [&](int x, int i, auto &dfs) {
        if (i == m) return void(res.insert(x));
        if (vis[x][i]) return;
        vis[x][i] = true;

        auto [d, dir] = moves[i];
        if (dir != -0) return dfs((x + d * dir + n) % n, i + 1, dfs);

        dfs((x + d) % n, i + 1, dfs);
        dfs((x - d + n) % n, i + 1, dfs);
    };
    dfs(st, 0, dfs);

    cout << res.size() << "\n";
    for (int v : res) cout << v + 1 << " ";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

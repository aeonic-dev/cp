#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;

    vec<string> s(n);
    rep(i, 0, n) cin >> s[i];

    int at;
    vec<int> ms;
    vec<vec<pair<int, char>>> adj(n * m);
    rep(i, 0, n) {
        rep(j, 0, m) {
            int ind = i * m + j;
            if (s[i][j] == 'A') at = ind;
            if (s[i][j] == 'M') ms.push_back(ind);
            if (s[i][j] == '#') continue;

            if (i > 0 && s[i - 1][j] != '#') adj[ind].emplace_back(ind - m, 'U');
            if (j > 0 && s[i][j - 1] != '#') adj[ind].emplace_back(ind - 1, 'L');
            if (i < n - 1 && s[i + 1][j] != '#') adj[ind].emplace_back(ind + m, 'D');
            if (j < m - 1 && s[i][j + 1] != '#') adj[ind].emplace_back(ind + 1, 'R');
        }
    }

    // shortest dist from a to any index; shortest dist from any monster
    vec<int> dista(n * m, INT_MAX), distm(n * m, INT_MAX);
    vec<pair<int, char>> par(n * m, {-1, 0});
    queue<pair<int, int>> q; // {index, dist}

    dista[at] = 0;
    q.emplace(at, 0);
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();

        if (d != dista[u]) continue;
        for (auto [v, dir] : adj[u]) {
            if (d + 1 < dista[v]) {
                dista[v] = d + 1, par[v] = {u, dir};
                q.emplace(v, d + 1);
            }
        }
    }

    for (auto mi : ms) {
        distm[mi] = 0;
        q.emplace(mi, 0);
    }
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();

        if (d != distm[u]) continue;
        for (auto [v, _] : adj[u]) {
            if (d + 1 < distm[v]) {
                distm[v] = d + 1;
                q.emplace(v, d + 1);
            }
        }
    }

    auto print = [&](int cur) -> void {
        cout << "YES\n" << dista[cur] << '\n';
        stack<char> path;
        while (par[cur].first != -1) path.push(par[cur].second), cur = par[cur].first;
        while (!path.empty()) cout << path.top(), path.pop();
    };

    rep(i, 1, n - 1) {
        rep(j, 0, 2) {
            int ind = (i + j) * m - j;
            if (s[ind / m][ind % m] == '#') continue;
            if (dista[ind] < distm[ind]) return print(ind);
        }
    }

    rep(i, 0, 2) {
        rep(j, 0, m) {
            int ind = i * (n - 1) * m + j;
            if (s[ind / m][ind % m] == '#') continue;
            if (dista[ind] < distm[ind]) return print(ind);
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

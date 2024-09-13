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
    vec<string> s(n);
    rep(i, 0, n) cin >> s[i];

    int start, end;
    vec<vec<pair<int, char>>> adj(n * m);
    rep(i, 0, n) {
        rep(j, 0, m) {
            char ch = s[i][j];
            if (ch == '#') continue;

            int ind = i * m + j;
            if (ch == 'A') start = ind;
            if (ch == 'B') end = ind;

            if (i > 0 && s[i - 1][j] != '#') adj[ind].emplace_back(ind - m, 'U');
            if (j > 0 && s[i][j - 1] != '#') adj[ind].emplace_back(ind - 1, 'L');
            if (i < n - 1 && s[i + 1][j] != '#') adj[ind].emplace_back(ind + m, 'D');
            if (j < m - 1 && s[i][j + 1] != '#') adj[ind].emplace_back(ind + 1, 'R');
        }
    }

    vec<pair<int, char>> par(n * m, {-1, 0});
    vec<int> dist(n * m, INT_MAX);
    priority_queue<pair<int, int>, vec<pair<int, int>>, greater<pair<int, int>>> pq; // {dist, node}
    dist[start] = 0, pq.emplace(0, start);

    while (!pq.empty()) {
        const auto &p = pq.top();
        int u = p.second, d = p.first;
        pq.pop();

        if (d != dist[u]) continue;
        for (const auto &e : adj[u]) {
            int v = e.first;
            char dir = e.second;

            if (d + 1 < dist[v]) {
                dist[v] = d + 1, par[v] = {u, dir};
                pq.emplace(d + 1, v);
            }
        }
    }

    if (dist[end] == INT_MAX) return void(cout << "NO");
    cout << "YES\n" << dist[end] << "\n";

    stack<char> path;
    int cur = end;
    while (par[cur].first != -1) path.push(par[cur].second), cur = par[cur].first;
    while (!path.empty()) cout << path.top(), path.pop();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

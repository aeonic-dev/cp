#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<int>> adj(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b, a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vec<int> col(n, 0);
    queue<pair<int, int>> q;

    int i = 0;
    while (!q.empty() or i < n - 1) {
        if (q.empty()) {
            while (i < n && col[i]) cout << col[i++] << ' ';
            if (i == n) break;
            q.emplace(i, 1);
        }
        int u = q.front().first, c = q.front().second;
        q.pop();

        col[u] = c;
        for (auto v : adj[u]) {
            if (col[v]) {
                if (col[v] == c) return void(cout << "IMPOSSIBLE\n");
                continue;
            }
            q.emplace(v, 3 - c);
        }
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

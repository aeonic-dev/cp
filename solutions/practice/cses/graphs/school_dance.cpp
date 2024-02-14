#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

bool dfs(int a, int L, vector<vi> &g, vi &btoa, vi &A, vi &B) {
    if (A[a] != L) return 0;
    A[a] = -1;
    for (int b : g[a])
        if (B[b] == L + 1) {
            B[b] = 0;
            if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
                return btoa[b] = a, 1;
        }
    return 0;
}

int hopcroftKarp(vector<vi> &g, vi &btoa) {
    int res = 0;
    vi A(g.size()), B(btoa.size()), cur, next;
    for (;;) {
        fill(all(A), 0);
        fill(all(B), 0);
        /// Find the starting nodes for BFS (i.e. layer 0).
        cur.clear();
        for (int a : btoa) if (a != -1) A[a] = -1;
        rep(a, 0, sz(g)) if (A[a] == 0) cur.push_back(a);
        /// Find all layers using bfs.
        for (int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for (int a : cur)
                for (int b : g[a]) {
                    if (btoa[b] == -1) {
                        B[b] = lay;
                        islast = 1;
                    } else if (btoa[b] != a && !B[b]) {
                        B[b] = lay;
                        next.push_back(btoa[b]);
                    }
                }
            if (islast) break;
            if (next.empty()) return res;
            for (int a : next) A[a] = lay;
            cur.swap(next);
        }
        /// Use DFS to scan for augmenting paths.
        rep(a, 0, sz(g))res += dfs(a, 0, g, btoa, A, B);
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vec<vi> g(n);
    rep(i, 0, k) {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
    }

    vi match(m, -1);
    auto res = hopcroftKarp(g, match);
    cout << res << '\n';
    rep(i, 0, m) {
        if (match[i] == -1) continue;
        cout << match[i] + 1 << ' ' << i + 1 << '\n';
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

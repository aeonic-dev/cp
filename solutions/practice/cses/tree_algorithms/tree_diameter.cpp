#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
vec<vi> adj;
vi dist;

// out is {d, i}
void dfs(int ind, pii &out, int d = 0) {
    if (d == 0) {
        dist = vi(n, -1);
        dist[ind] = 0;
    }

    for (int cur: adj[ind]) {
        if (dist[cur] != -1) {
            dist[cur] = max(dist[cur], d + 1);
            continue;
        }

        out = max(out, {dist[cur] = d + 1, cur});
        dfs(cur, out, d + 1);
    }
}

void solve() {
    cin >> n;
    adj = vec<vec<int>>(n);
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;

        adj[--a].push_back(--b);
        adj[b].push_back(a);
    }

    pii res = {0, 0};
    dfs(0, res);

    int s = res.second;
    dfs(s, res = {0, 0});

    cout << res.first << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

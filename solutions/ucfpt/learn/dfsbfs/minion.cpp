#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int t;
    cin >> t;
    string s;
    set<string> cant;
    rep(i, 0, t) {
        cin >> s;
        cant.insert(s);
    }

    int n, e, a, b;
    cin >> n >> e;
    vec<vec<int>> adj(n);
    rep(i, 0, e) {
        cin >> a >> b >> s;
        if (cant.count(s)) continue;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bitset<30> vs;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vs[u] = 1;

        if (u == n - 1) {
            cout << "1\n";
            return;
        }

        for (auto v : adj[u]) {
            if (vs[v]) continue;
            q.push(v);
        }
    }

    cout << "0\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

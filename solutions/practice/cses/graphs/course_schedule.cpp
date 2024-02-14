#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;
typedef vector<int> vi;

vi topoSort(const vector<vi> &gr) {
    vi indeg(gr.size()), ret;
    for (auto &li : gr) for (int x : li) indeg[x]++;
    queue<int> q; // use priority_queue for lexic. largest ans.
    rep(i, 0, gr.size()) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int i = q.front(); // top() for priority queue
        ret.push_back(i);
        q.pop();
        for (int x : gr[i])
            if (--indeg[x] == 0) q.push(x);
    }
    return ret;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vi> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }

    auto res = topoSort(adj);
    if (res.size() < n) cout << "IMPOSSIBLE";
    else for (auto r : res) cout << r + 1 << ' ';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

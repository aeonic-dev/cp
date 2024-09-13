#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

vi topoSort(const vector<vi> &gr) {
    vi indeg(sz(gr)), ret;
    for (auto &li : gr) for (int x : li) indeg[x]++;
    queue<int> q; // use priority_queue for lexic. largest ans.
    rep(i, 0, sz(gr)) if (indeg[i] == 0) q.push(i);
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
    while (cin >> n >> m, n && m) {
        vector<vi> adj(n);
        rep(i, 0, m) {
            int u, v;
            cin >> u >> v, u--, v--;
            adj[u].push_back(v);
        }
        
        vi res = topoSort(adj);
        if (sz(res) < n) {
            cout << "0\n";
            continue;
        }
        
        rep(i, 1, n) {
            int u = res[i - 1], v = res[i];
            if (!count(all(adj[u]), v)) {
                cout << "2\n";
                goto next;
            }
        }
        cout << "1\n";
        next:;
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

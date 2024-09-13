#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;
    
    LCA(vector<vi> &C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi> &C, int v, int par) {
        time[v] = T++;
        for (int y : C[v])
            if (y != par) {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v);
            }
    }
    
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
//    dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

void solve() {
    int n;
    cin >> n;
    vector<vi> gr(n);
    rep(i, 1, n) {
        int u, v;
        cin >> u >> v, u--, v--;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    
    vi depth(n);
    auto dfs = [&](int u, int p, int d, auto &dfs) -> void {
        depth[u] = d;
        for (int v : gr[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1, dfs);
        }
    };
    dfs(0, 0, 0, dfs);
    LCA lca(gr);
    
    vi perm(n);
    for (int &x : perm) cin >> x, x--;
    rep(i, 1, n) {
        int u = perm[i - 1], v = perm[i];
        int dist = depth[u] + depth[v] - 2 * depth[lca.lca(u, v)];
        if (dist > 3) return void(cout << "0\n");
    }
    cout << "1\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}

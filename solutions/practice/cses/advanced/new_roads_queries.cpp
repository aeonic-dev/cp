#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct dsu {
    vector<int> par;
    dsu(int n) : par(n, -1) {}
    
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (par[a] > par[b]) swap(a, b); // a is larger
        par[a] += par[b], par[b] = a;
        return true;
    }
    
    int find(int s) {
        return par[s] < 0 ? s : par[s] = find(par[s]);
    }
    
    int count() {
        int num = 0;
        for (auto &p : par) num += p < 0;
        return num;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> ed(m), qi(k);
    rep(i, 0, m) {
        auto &[u, v] = ed[i];
        cin >> u >> v, u--, v--;
    }
    rep(i, 0, k) {
        auto &[a, b] = qi[i];
        cin >> a >> b, a--, b--;
    }
    
    vector<queue<int>> md(m);
    vi lo(k, 0), hi(k, m - 1), res(k, -1);
    rep(i, 0, k) md[m / 2].push(i);
    
    int num = 0; // # of queries answered
    while (num < k) {
        dsu ds(n);
        rep(i, 0, m) {
            auto [u, v] = ed[i];
            ds.join(u, v);
            
            auto &qs = md[i];
            while (!qs.empty()) {
                int q = qs.front();
                qs.pop();
                
                if (lo[q] >= hi[q]) {
                    res[q] = i, num++;
                    continue;
                }
                
                auto [a, b] = qi[q];
                if (ds.find(a) == ds.find(b)) hi[q] = i;
                else lo[q] = i + 1;
                md[(lo[q] + hi[q]) / 2].push(q);
            }
        }
    }
    
    dsu ds(n);
    for (auto [u, v] : ed) ds.join(u, v);
    rep(i, 0, k) {
        auto [a, b] = qi[i];
        if (a == b) {
            cout << "0\n";
            continue;
        }
        
        if (ds.find(a) == ds.find(b)) cout << res[i] + 1 << "\n";
        else cout << "-1\n";
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

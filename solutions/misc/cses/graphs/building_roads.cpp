#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

struct dsu {
    vector<int> par;
    dsu(int n) : par(n, -1) {}

    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (par[a] > par[b]) swap(a, b); // a is larger
        par[a] += par[b];
        par[b] = a;

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
    int n, m;
    cin >> n >> m;

    dsu s(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v, u--, v--;
        s.join(u, v);
    }

    set<int> res;
    rep(i, 0, n) res.insert(s.find(i));
    cout << res.size() - 1 << "\n";
    int last = -1;
    for (auto r: res) {
        if (last != -1) cout << last + 1 << " " << r + 1 << "\n";
        last = r;
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

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
#define sz(x) (x).size()
typedef long long ll;
typedef vector<int> vi;

int topoSort(const vector<vi> &gr) {
    int num = 0;
    vi indeg(sz(gr));
    for (auto &li : gr) for (int x : li) indeg[x]++;
    queue<int> q; // use priority_queue for lexic. largest ans.
    rep(i, 0, sz(gr)) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int i = q.front(); // top() for priority queue
        num++;
        q.pop();
        for (int x : gr[i])
            if (--indeg[x] == 0) q.push(x);
    }
    return num;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vec<vi> g(n);
    vec<bitset<200000>> added(n);

    vi tmp(n);
    rep(i, 0, k) {
        rep(j, 0, n) {
            cin >> tmp[j], tmp[j]--;
            rep(l, 1, j) {
                int u = tmp[l], v = tmp[j];
                if (added[u][v]) continue;
                added[u][v] = true;
                g[u].push_back(v);
            }
        }
    }

    int num = topoSort(g);
    if (num < n) return void(cout << "no\n");
    cout << "yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

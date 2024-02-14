#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vec<vec<pair<int, ll>>> adj(n);
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
    }

    vec<ll> nums(n, 0);
    priority_queue<pair<ll, int>, vec<pair<ll, int>>, greater<>> q;
    q.emplace(0, 0);

    while (!q.empty() && nums[n - 1] < k) {
        auto [d, u] = q.top();
        q.pop();

        if (nums[u] >= k) continue;
        nums[u]++;
        if (u == n - 1) cout << d << ' ';
        for (auto [v, w] : adj[u])
            q.emplace(d + w, v);;
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

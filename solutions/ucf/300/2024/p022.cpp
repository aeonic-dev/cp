#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, m, k;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w, u--, v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<vll> dist(n, vll(n, LLONG_MAX));
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    rep(i, 0, n) {
        pq.emplace(dist[i][i] = 0, i);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (dist[i][u] != d) continue;
            for (auto [v, w] : adj[u]) {
                if (d + w >= dist[i][v]) continue;
                pq.emplace(dist[i][v] = d + w, v);
            }
        }
    }


    cin >> k;
    vector<tuple<ll, int, ll>> orders(k); // {time placed, vertex, time ready}
    for (auto &[tp, v, tr] : orders) cin >> tp >> v >> tr, v--;

    auto check = [&](ll maxw) -> bool {
        // latest start time for all trips in [i, k)
        vector<ll> maxt(k, -1);
        maxt[k - 1] = get<0>(orders[k - 1])
                      + maxw
                      - dist[0][get<1>(orders[k - 1])];

        for (int l = k - 2; l >= 0; l--) {
            auto &&[tp_u, u, tr_u] = orders[l];

            int last = 0;
            ll taken = 0,
               max_st = LLONG_MAX;

            rep(r, l, k) {
                auto &&[tp_v, v, tr_v] = orders[r];
                taken += dist[last][v];

                max_st = min(max_st,
                             tp_v + maxw - taken);
                if (max_st < tr_v) break;

                ll max_st_next = (r == k - 1) ? LLONG_MAX
                                              : maxt[r + 1] - dist[v][0] - taken;
                if (max_st_next >= tr_v)
                    maxt[l] = max(maxt[l],
                                  min(max_st,
                                      max_st_next));
                last = v;
            }
        }

        return maxt[0] >= 0; //get<2>(orders[0]);
    };


    ll lo = 0, hi = LLONG_MAX;
    while (lo != hi) {
        ll md = lo + (hi - lo) / 2;
        if (!check(md)) lo = md + 1;
        else hi = md;
    }
    cout << lo << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

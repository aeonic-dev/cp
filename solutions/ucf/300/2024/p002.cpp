#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const ld pi = acos(-1);
void solve() {
    int c, n;
    cin >> c >> n;
    vi rads(c);
    for (int &rad : rads) cin >> rad;
    vector<vector<pair<ld, int>>> pts(c); // [circle_index] = {{angle, node index}}
    vector<vector<pair<int, ld>>> adj(2 * n + 2); // {v, w}
    rep(i, 0, n) {
        int id = 2 * (i + 1);
        int d, tmp;
        cin >> d >> tmp, d--;

        ld th = (tmp % 360) * pi / 180.l;
        pts[d].emplace_back(th, id);
        pts[d + 1].emplace_back(th, id + 1);

        adj[id].emplace_back(id + 1, rads[d + 1] - rads[d]);
        adj[id + 1].emplace_back(id, rads[d + 1] - rads[d]);
    }

    int sc, sa, fc, fa;
    cin >> sc >> sa >> fc >> fa, sc--, fc--;
    ld th1 = (sa % 360) * pi / 180.l;
    ld th2 = (fa % 360) * pi / 180.l;
    pts[sc].emplace_back(th1, 0);
    pts[fc].emplace_back(th2, 1);

    //    int i = 0;
    //    cout << "\n";
    //    for (auto &vec : pts) {
    //        cout << "i = " << i++ << " {\n";
    //        for (auto &[th, id] : vec) {
    //            cout << "\t" << id << " @ " << th << "\n";
    //        }
    //        cout << "}\n";
    //    }

    rep(i, 0, c) {
        auto &vec = pts[i];
        sort(all(vec));

        int m = sz(vec);
        if (m <= 1) continue;

        rep(j, 0, m) {
            if (m == 2 && j == m - 1) break; // skip duplicate edges with m=2
            auto [th_u, u] = vec[j];
            auto [th_v, v] = vec[(j + 1) % m];

            ld delta = abs(th_v - th_u);
            if (delta > pi) delta = 2 * pi - delta;
            // cout << u << "->" << v << " delta = " << delta << "\n";
            ld w = delta * rads[i];

            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
    }

    //    cout << "\n";
    //    rep(u, 0, 2 * n + 2) {
    //        cout << "u = " << u << " {\n";
    //        for (auto [v, w] : adj[u]) {
    //            cout << "\t-> " << v << " = " << w << "\n";
    //        }
    //        cout << "}\n";
    //    }

    vector<ld> dist(2 * n + 2, 1e20l);
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<>> pq;
    pq.emplace(dist[0] = 0, 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        // assert(d >= 0);

        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w >= dist[v]) continue;
            // cout << u << "->" << v << " = " << w << " : " << d + w << "\n";
            pq.emplace(dist[v] = d + w, v);
        }
    }

    cout << dist[1] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(2) << fixed;

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

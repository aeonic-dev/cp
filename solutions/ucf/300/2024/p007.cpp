#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

struct P {
    int r, c;
    P(int r = 0, int c = 0) : r(r), c(c) {}
    bool operator<(P o) const { return tie(r, c) < tie(o.r, o.c); }
    bool operator==(P o) const { return tie(r, c) == tie(o.r, o.c); }
};
typedef bitset<36> B;
typedef unsigned long ul;

bool at(const B &bs, int r, int c) { return bs[r * 6 + c]; }
void set_at(B &bs, int r, int c, bool v = 0) { bs[r * 6 + c] = v; }
vector<B> get_moves(const B &b) {
    vector<B> res;
    rep(r, 0, 6) rep(c, 0, 6) {
        if (!at(b, r, c)) continue;

        B nb = b;
        set_at(nb, r, c, 0);
        int nr, nc;
        for (nr = r + 1; nr < 6 && !at(b, nr, c); nr++);
        nr--, set_at(nb, nr, c, 1), res.push_back(nb);

        nb = b, set_at(nb, r, c, 0);
        for (nr = r - 1; nr >= 0 && !at(b, nr, c); nr--);
        nr++, set_at(nb, nr, c, 1), res.push_back(nb);

        nb = b, set_at(nb, r, c, 0);
        for (nc = c + 1; nc < 6 && !at(b, r, nc); nc++);
        nc--, set_at(nb, r, nc, 1), res.push_back(nb);

        nb = b, set_at(nb, r, c, 0);
        for (nc = c - 1; nc >= 0 && !at(b, r, nc); nc--);
        nc++, set_at(nb, r, nc, 1), res.push_back(nb);
    }
    res.erase(remove_if(all(res), [&](const B &x) { return x == b; }), end(res));
    return res;
}

void solve() {
    B s, e;
    rep(i, 0, 4) {
        int r, c;
        cin >> r >> c;
        set_at(s, r, c, 1);
    }
    rep(i, 0, 4) {
        int r, c;
        cin >> r >> c;
        set_at(e, r, c, 1);
    }
    map<ul, B> par;
    map<ul, int> dist;
    queue<pair<int, B>> q;

    q.emplace(dist[s.to_ulong()] = 0, s);
    while (!q.empty()) {
        auto [d, u] = q.front();
        q.pop();

        if (u == e) break;

        // cout << "d: " << d << "\nu: ";
        // rep(r, 0, 6) {
        //     rep(c, 0, 6) {
        //         if (at(u, r, c)) cout << "(" << r << ", " << c << ") ";
        //     }
        // }
        // cout << "\n";

        if (d != dist[u.to_ulong()]) continue;
        vector<B> to = get_moves(u);
        for (const auto &v : to) {
            // cout << "v: ";
            // for (auto [r, c] : v) cout << "(" << r << ", " << c << ") ";
            // cout << "\n";

            int nd = dist[u.to_ulong()] + 1;
            if (!dist.count(v.to_ulong()) || nd < dist[v.to_ulong()]) {
                par[v.to_ulong()] = u;
                q.emplace(dist[v.to_ulong()] = nd, v);
            }
        }
    }
    cout << dist[e.to_ulong()] << "\n";
    vector<B> path;
    for (B u = e; u != s; u = par[u.to_ulong()]) path.push_back(u);
    path.push_back(s);

    reverse(all(path));
    rep(i, 1, sz(path)) {
        B diff = path[i] ^ path[i - 1];
        rep(r, 0, 6) rep(c, 0, 6) {
            if (at(diff, r, c) && at(path[i - 1], r, c)) {
                cout << r << " " << c << " ";
                break;
            }
        }
        rep(r, 0, 6) rep(c, 0, 6) {
            if (at(diff, r, c) && at(path[i], r, c)) {
                cout << r << " " << c << "\n";
                break;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

typedef array<array<int8_t, 3>, 3> B;
istream &operator>>(istream &is, int8_t &ov) {
    int iv;
    return is >> iv, ov = iv, is;
};

void print(const B &b) {
    for (auto &r : b) {
        for (auto &x : r) cout << x << " ";
        cout << "\n";
    }
    cout << "\n";
}

void solve() {
    B tgt;
    ::iota(&tgt[0][0], &tgt[3][0], 1), tgt[2][2] = 0;

    map<B, int> dist;
    queue<pair<B, int>> q;

    q.push({tgt, 0});
    while (sz(q)) {
        auto [u, d] = q.front();
        q.pop();

        if (dist.count(u)) continue;
        dist[u] = d;

        rep(i, 0, 3) rep(j, 0, 3) if (!u[i][j]) {
            for (int di : {-1, 1}) {
                if (0 <= i + di && i + di < 3) {
                    swap(u[i][j], u[i + di][j]);
                    q.push({u, d + 1});
                    swap(u[i][j], u[i + di][j]);
                }
                if (0 <= j + di && j + di < 3) {
                    swap(u[i][j], u[i][j + di]);
                    q.push({u, d + 1});
                    swap(u[i][j], u[i][j + di]);
                }
            }
    }
    }

    int n;
    cin >> n;
    rep(i, 0, n) {
        B st;
        for (auto &r : st)
            for (auto &x : r) cin >> x;
        int res = dist[st];
        cout << res << "\n";
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

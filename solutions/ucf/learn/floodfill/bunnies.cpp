#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> gr(n);
    rep(i, 0, n) cin >> gr[i];

    vector<bitset<10>> vis(n);
    auto go = [&](int i, int j, auto &&go) -> bool {
        if (i < 0 || j < 0 || i >= n || j >= m) return false;
        if (vis[i][j] || gr[i][j] == '#') return false;
        vis[i][j] = true;

        if (gr[i][j] == 'C') return true;
        return go(i - 1, j, go)
               || go(i + 1, j, go)
               || go(i, j - 1, go)
               || go(i, j + 1, go);
    };
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (gr[i][j] != 'P') continue;
            if (go(i, j, go)) cout << "yes\n";
            else cout << "no\n";
            return;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

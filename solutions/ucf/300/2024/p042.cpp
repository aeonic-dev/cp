#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

// bottom, left, back, front, right, top
typedef array<int, 6> C;
#define D c[0]
#define L c[1]
#define B c[2]
#define F c[3]
#define R c[4]
#define U c[5]

void rot_r(C &c) { swap(D, L), swap(D, U), swap(D, R); }
void rot_l(C &c) { swap(D, R), swap(D, U), swap(D, L); }
void rot_d(C &c) { swap(D, F), swap(F, B), swap(F, U); }
void rot_u(C &c) { swap(F, U), swap(F, B), swap(D, F); }

void solve() {
    int n;
    cin >> n;
    vector<vi> col(n, vi(n));
    rep(i, 0, n) rep(j, 0, n) cin >> col[i][j];

    vector<vector<set<C>>> vis(n, vector<set<C>>(n));
    auto dfs = [&](int i, int j, C &c, auto &&dfs) -> bool {
        if (i < 0 || i >= n || j < 0 || j >= n) return false;
        if (D != -1 && D != col[i][j]) return false;
        int old_d = D;
        D = col[i][j];

        if (i == n - 1 && j == n - 1) return true;

        // TODO: could do a better check here where -1s disqualify too
        if (vis[i][j].count(c))
            return D = old_d, false;
        vis[i][j].insert(c);


        if (rot_r(c), dfs(i, j + 1, c, dfs))
            return rot_l(c), true;
        rot_l(c);

        if (rot_d(c), dfs(i + 1, j, c, dfs))
            return rot_u(c), true;
        rot_u(c);

        D = old_d;
        return false;
    };

    C c{-1, -1, -1, -1, -1, -1};
    if (dfs(0, 0, c, dfs)) {
        cout << "Yes\n";
        rep(i, 0, 6) cout << max(0, c[i]) << " \n"[i == 5];
        return;
    }

    cout << "No\n";
}

int main() {
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

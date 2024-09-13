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
    vector<vi> pfx(n + 1, vi(m + 1, 0));
    rep(i, 0, n) {
        cin >> gr[i];
        rep(j, 0, m) {
            pfx[i + 1][j + 1] = pfx[i][j + 1]
                                + pfx[i + 1][j]
                                - pfx[i][j]
                                + (gr[i][j] == '#');
        }
    }

    // try splitting at all rows
    rep(r, 1, n) { // a will be within [0, r), b in [r, n-1]
        // find min and max row/col of a filled cell in both a and b
        int mini_a = n, maxi_a = -1, minj_a = m, maxj_a = -1;
        int mini_b = n, maxi_b = -1, minj_b = m, maxj_b = -1;
        rep(i, 0, n) {
            rep(j, 0, m) {
                if (gr[i][j] != '#') continue;
                if (i < r) {
                    mini_a = min(mini_a, i), maxi_a = max(maxi_a, i);
                    minj_a = min(minj_a, j), maxj_a = max(maxj_a, j);
                } else {
                    mini_b = min(mini_b, i), maxi_b = max(maxi_b, i);
                    minj_b = min(minj_b, j), maxj_b = max(maxj_b, j);
                }
            }
        }

        // cout << "split row " << r << "\n"; // debug
        // cout << "a: [" << mini_a << ", " << maxi_a << "] -> [" << minj_a << ", " << maxj_a << "]\n";
        // cout << "b: [" << mini_b << ", " << maxi_b << "] -> [" << minj_b << ", " << maxj_b << "]\n";

        if (mini_a == n || mini_b == n) continue; // no filled cells in a or b
        int pfx_a = pfx[maxi_a + 1][maxj_a + 1]
                    - pfx[mini_a][maxj_a + 1]
                    - pfx[maxi_a + 1][minj_a]
                    + pfx[mini_a][minj_a];
        int pfx_b = pfx[maxi_b + 1][maxj_b + 1]
                    - pfx[mini_b][maxj_b + 1]
                    - pfx[maxi_b + 1][minj_b]
                    + pfx[mini_b][minj_b];

        // cout << "pfx_a: " << pfx_a << ", should be " << (maxi_a - mini_a + 1) * (maxj_a - minj_a + 1) << '\n';
        // cout << "pfx_b: " << pfx_b << ", should be " << (maxi_b - mini_b + 1) * (maxj_b - minj_b + 1) << '\n';

        if (pfx_a != (maxi_a - mini_a + 1) * (maxj_a - minj_a + 1)) continue;
        if (pfx_b != (maxi_b - mini_b + 1) * (maxj_b - minj_b + 1)) continue;

        // pog
        cout << "YES\n";
        rep(i, 0, n) {
            rep(j, 0, m) {
                if (i >= mini_a && i <= maxi_a && j >= minj_a && j <= maxj_a) cout << 'a';
                else if (i >= mini_b && i <= maxi_b && j >= minj_b && j <= maxj_b) cout << 'b';
                else cout << '.';
            }
            cout << "\n";
        }
        return;
    }

    // code duplication my beloved
    rep(c, 1, m) {
        int mini_a = n, maxi_a = -1, minj_a = m, maxj_a = -1;
        int mini_b = n, maxi_b = -1, minj_b = m, maxj_b = -1;
        rep(i, 0, n) {
            rep(j, 0, m) {
                if (gr[i][j] != '#') continue;
                if (j < c) {
                    mini_a = min(mini_a, i), maxi_a = max(maxi_a, i);
                    minj_a = min(minj_a, j), maxj_a = max(maxj_a, j);
                } else {
                    mini_b = min(mini_b, i), maxi_b = max(maxi_b, i);
                    minj_b = min(minj_b, j), maxj_b = max(maxj_b, j);
                }
            }
        }

        // cout << "split col " << c << "\n"; // debug
        // cout << "a: [" << mini_a << ", " << maxi_a << "] -> [" << minj_a << ", " << maxj_a << "]\n";
        // cout << "b: [" << mini_b << ", " << maxi_b << "] -> [" << minj_b << ", " << maxj_b << "]\n";

        if (mini_a == n || mini_b == n) continue; // no filled cells in a or b
        int pfx_a = pfx[maxi_a + 1][maxj_a + 1]
                    - pfx[mini_a][maxj_a + 1]
                    - pfx[maxi_a + 1][minj_a]
                    + pfx[mini_a][minj_a];
        int pfx_b = pfx[maxi_b + 1][maxj_b + 1]
                    - pfx[mini_b][maxj_b + 1]
                    - pfx[maxi_b + 1][minj_b]
                    + pfx[mini_b][minj_b];
        // cout << "pfx_a: " << pfx_a << ", should be " << (maxi_a - mini_a + 1) * (maxj_a - minj_a + 1) << '\n';
        // cout << "pfx_b: " << pfx_b << ", should be " << (maxi_b - mini_b + 1) * (maxj_b - minj_b + 1) << '\n';

        if (pfx_a != (maxi_a - mini_a + 1) * (maxj_a - minj_a + 1)) continue;
        if (pfx_b != (maxi_b - mini_b + 1) * (maxj_b - minj_b + 1)) continue;

        cout << "YES\n";
        rep(i, 0, n) {
            rep(j, 0, m) {
                if (i >= mini_a && i <= maxi_a && j >= minj_a && j <= maxj_a) cout << 'a';
                else if (i >= mini_b && i <= maxi_b && j >= minj_b && j <= maxj_b) cout << 'b';
                else cout << '.';
            }
            cout << "\n";
        }
        return;
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

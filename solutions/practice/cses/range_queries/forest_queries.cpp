#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, q;
    cin >> n >> q;
    vec<vec<int>> pfx(n + 1, vec<int>(n + 1, 0));
    rep(i, 0, n) {
        string s;
        cin >> s;
        rep(j, 0, n) {
            pfx[i + 1][j + 1] =
                    pfx[i][j + 1] + pfx[i + 1][j] - pfx[i][j] +
                    (s[j] == '*');
        }
    }

    rep(qi, 0, q) {
        int i, j, k, l;
        cin >> i >> j >> k >> l;
        cout << pfx[k][l] - pfx[k][j - 1] - pfx[i - 1][l] + pfx[i - 1][j - 1] << "\n\n";
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

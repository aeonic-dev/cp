#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void dfs(int n, int m, vec<string> &s, vec<bitset<1000>> &v, int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) return;
    if (v[i][j] || s[i][j] == '#') return;

    v[i][j] = true;
    dfs(n, m, s, v, i, j + 1);
    dfs(n, m, s, v, i, j - 1);
    dfs(n, m, s, v, i + 1, j);
    dfs(n, m, s, v, i - 1, j);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<string> s(n);
    rep(i, 0, n) cin >> s[i];

    vec<bitset<1000>> v(n);
    int num = 0;

    rep(i, 0, n) {
        rep(j, 0, m) {
            auto ch = s[i][j];
            if (ch == '#' || v[i][j]) continue;

            dfs(n, m, s, v, i, j);
            num++;
        }
    }

    cout << num << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

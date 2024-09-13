#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

ll go(vec<bitset<8>> &board, bitset<16> &col, bitset<16> &d1, bitset<16> &d2, int r = 0) {
    if (r == 8) return 1;

    ll res = 0;
    rep(c, 0, 8) {
        if (board[r][c] || col[c] || d1[r + c] || d2[r - c + 7]) continue;

        col[c] = d1[r + c] = d2[r - c + 7] = 1;
        res += go(board, col, d1, d2, r + 1);
        col[c] = d1[r + c] = d2[r - c + 7] = 0;
    }

    return res;
}

void solve() {
    vec<bitset<8>> board(9);
    bitset<16> col, d1, d2;
    rep(i, 0, 8) {
        string s;
        cin >> s;
        rep(j, 0, 8) board[i][j] = (s[j] == '*') ? -1 : 0;
    }

    ll res = go(board, col, d1, d2);
    cout << res << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

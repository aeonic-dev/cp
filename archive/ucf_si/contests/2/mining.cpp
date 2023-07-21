// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// primitive types
typedef long long ll;
typedef long int li;

// aliases
#define vec vector
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// meta macros
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define THANKS void GIVE_ME_A_SEMICOLON() // requires semicolon when calling a macro

// more aliases
#define pb push_back
#define eb emplace_back
#define mp make_pair

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

ll sum_range(li **pfx, li n, li r1, li c1, li r2, li c2) {
    r1 = max(r1, 1l);
    c1 = max(c1, 1l);
    r2 = min(r2, n);
    c2 = min(c2, n);

    return pfx[r2][c2] - pfx[r1 - 1][c2] - pfx[r2][c1 - 1] + pfx[r1 - 1][c1 - 1];
}

void solve() {
    int n, q;
    cin >> n >> q;

    int gold[n][n];
    li **pfx = new li *[n + 1];
    rep(i, 0, n + 1) {
        pfx[i] = new li[n + 1];
        memset(pfx[i], 0, (n + 1) * sizeof(int));
    }

    rep(i, 0, n) {
        rep(j, 0, n) {
            cin >> gold[i][j];
            pfx[i + 1][j + 1] = gold[i][j] + pfx[i][j + 1] + pfx[i + 1][j] - pfx[i][j];
        }
    }

    int c, r, d;
    rep(i, 0, q) {
        cin >> c >> r >> d;

        if (d == 0) {
            cout << gold[r - 1][c - 1] << endl;
            continue;
        }

        ll sum = 0;
        if (c - d >= 1) sum += gold[r - 1][c - 1 - d];
        if (c + d <= n) sum += gold[r - 1][c - 1 + d];
        if (r - d >= 1) sum += gold[r - 1 - d][c - 1];
        if (r + d <= n) sum += gold[r - 1 + d][c - 1];
//        gold[r - 1][c - 1 - d] + gold[r - 1][c - 1 + d] + gold[r - 1 - d][c - 1] + gold[r - 1 + d][c - 1];

        rep(j, 1, (int) ceil(d / 2.0)) {
            sum += sum_range(pfx, n, r - d + j, c - j, r + d - j, c + j) -
                   sum_range    (pfx, n, r - d + j + 1, c - j, r + d - j - 1, c + j) +
                   sum_range(pfx, n, r - j, c - d + j, r + j, c + d - j) -
                   sum_range(pfx, n, r - j, c - d + j + 1, r + j, c + d - j - 1);
        }

        int d2 = d / 2;
        sum += sum_range(pfx, n, r - d2, c - d2, r + d2, c + d2);

        cout << sum << endl;
    }

    delete[] pfx;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
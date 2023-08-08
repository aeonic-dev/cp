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

// more aliases
#define pb push_back
#define eb emplace_back
#define mp make_pair

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define trav(x, s) for (auto x: s)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

pair<bool, int> check(vec<bitset<1000>> &grid, int r, int c, bitset<1000> &rows, bitset<1000> &cols) {
    int activations = rows[0] ? 1 : 0;
    rep(i, 0, r) {
        rep(j, 0, c) {
            if (i == 0) activations += (cols[j] = grid[0][j] ^ rows[0]);
            else {
                if (j == 0) activations += (rows[i] = grid[i][0] ^ cols[0]);
                else if (grid[i][j] != (rows[i] ^ cols[j])) return {false, activations};
            }
        }
    }

    return {true, activations};
}

void print(bitset<1000> &rows, bitset<1000> &cols, int r, int c) {
    rep(i, 0, r) cout << rows[i] << " ";
    cout << endl;
    rep(i, 0, c) cout << cols[i] << " ";
    cout << endl;
}

void solve() {
    int r, c;
    cin >> r >> c;

    vec<bitset<1000>> grid(r);

    char ch;
    rep(i, 0, r) {
        rep(j, 0, c) {
            cin >> ch;
            grid[i][j] = ch == '1';
        }
        cin.ignore();
    }

    bitset<1000> rows1, rows2(0b1), cols1, cols2;
    pair<bool, int> a, b;
    a = check(grid, r, c, rows1, cols1);
    b = check(grid, r, c, rows2, cols2);

    if (a.first && a.second <= b.second) {
        print(rows1, cols1, r, c);
        return;
    } else if (b.first) {
        print(rows2, cols2, r, c);
        return;
    }

    cout << "impossible\n";
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
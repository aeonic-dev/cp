// Settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// Few word type fast zoom
#define vec vector
#define pb push_back
#define eb emplace_back

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<li, li> pli;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// Other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
// @formatter:on

vec<vec<bool>> visited;

bool find_path(vec<vec<bool>> &rows, int n, int i, int j) {
    if (!rows[j][i]) return false;
    if (i >= n - 1) return true;

    visited[j][i] = true;

    if (!visited[j][i + 1] && find_path(rows, n, i + 1, j)) return true;
    if (j > 0 && !visited[j - 1][i] && find_path(rows, n, i, j - 1)) return true;
    if (j < 2 && !visited[j + 1][i] && find_path(rows, n, i, j + 1)) return true;

    return false;
}

bool find_path(vec<vec<bool>> &rows, int n, int row) {
    visited = vec<vec<bool>>(rows.size(), vec<bool>(rows[0].size(), false));
    return find_path(rows, n, 0, row);
}

void solve() {
    int n;
    cin >> n;

    vec<vec<bool>> rows(3, vec<bool>(n));
    rep(i, 0, 3) {
        rep(j, 0, n) {
            char c;
            cin >> c;

            rows[i][j] = c == '0';
        }
        cin.ignore();
    }

    bool solvable = find_path(rows, n, 0) || find_path(rows, n, 1) || find_path(rows, n, 2);
    cout << (solvable ? "Solvable!\n" : "Unsolvable!\n") << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)
    cout << setprecision(4) << fixed;

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
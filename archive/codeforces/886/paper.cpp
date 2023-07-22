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

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

void solve() {
    vec<vec<char>> chars(8, vec<char>(8));

    int col = -1;
    string ret;

    rep(i, 0, 8) {
        rep(j, 0, 8) {
            cin >> chars[i][j];
            if (col == -1) {
                if (chars[i][j] != '.') {
                    col = j;
                    ret.push_back(chars[i][j]);
                }
            } else {
                if (j == col && chars[i][j] != '.') {
                    ret.push_back(chars[i][j]);
                }
            }
        }

        cin.ignore();
    }

    cout << ret << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}
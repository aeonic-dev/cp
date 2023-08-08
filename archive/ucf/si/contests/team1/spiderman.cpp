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
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

//pair<int, bitset<40>> min_height(vec<bitset<40>> &dp, vec<int> &moves, int i, int h, int max_h) {
////    if (i >= moves.size()) return {h == 0 ? max_h : INT_MAX, bitset<40>()};
////
////    if (moves[i] > h) {
////        // 0=down, +1=up
////        dp[i * 2].set(i, false);
////        return min_height(dp, moves, i + 1, h + moves[i], max_h);
////    }
////
////    vec<int> r1;
////
//////    return min(
//////            min_height(moves, i + 1, h + moves[i], max(max_h, h + moves[i])),
//////            min_height(moves, i + 1, h - moves[i], max(max_h, h))
//////    );
//}

pair<int, bitset<40>> min_height_path(pair<int, bitset<40>> &path, vec<int> &moves, int i, int h) {
    pair<int, bitset<40>> ret = {path.first, path.second};

}

void solve() {
    int m;
    cin >> m;

    vec<int> moves(m);
    rep(i, 0, m) cin >> moves[i];

    vec<bitset<40>> dp(m * 2);

    cout << min_height(dp, moves, 0, 0, 0) << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    cout << setprecision(2) << fixed;
//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}
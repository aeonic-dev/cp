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
#define numeric(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

float cost(vec<vec<float>> &dp, vec<vec<float>> &edges, int n, int mask, int last) {
    if (mask == 0) return edges[last][0];

    if (dp[mask][last] == -1) {
        float cost = DBL_MAX;
        rep(i, 0, n) {
            if ((mask & (1 << i)) == 0) continue;
            cost = min(cost, edges[last][i] + ::cost(dp, edges, n, mask ^ (1 << i), i));
        }
        dp[mask][last] = cost;
    }

    return dp[mask][last];
}

void solve() {
    int n;
    cin >> n;

    vec<vec<float>> dp(1 << n), edges(n);
    rep(i, 0, 1 << n) dp[i] = vec<float>(n, -1);
    rep(i, 0, n) {
        edges[i] = vec<float>(n);

        rep(j, 0, n) cin >> edges[i][j];
    }

    cout << setprecision(2) << fixed << round(cost(dp, edges, n, (1 << n) - 2, 0) * 100) / 100 << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}

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
#define uset unordered_set
#define umap unordered_map

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
#define gin(type) get_cin<type>()

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
// @formatter:on

ll solve(int k, vec<pair<int, pi>> &dvw, vec<vll> &dp, int next, int day) {
    if (next >= k) return 0;

    auto d = dvw[next].first,
            v = dvw[next].second.first, w = dvw[next].second.second;


    auto &res = dp[next][day];
    if (res == -1) {
        // past when we can take this prize
        if (d < day) return solve(k, dvw, dp, next + 1, day);
        if (d > day) day = d;

        res = solve(k, dvw, dp, next + 1, day);
        res = max(res,
                  v + solve(k, dvw, dp, next + 1, day + w)
        );
    }

    return res;
}

void solve() {
    int k;
    cin >> k;

    // day, value, wait time
    int max_day = INT_MIN;
    vec<pair<int, pi>> dvw(k);
    rep(i, 0, k) {
        cin >> dvw[i];
        max_day = max(max_day, dvw[i].first + dvw[i].second.second);
    }
    sort(all(dvw));

    // index, day
    vec<vll> dp(k, vll(max_day + 1, -1));
    cout << solve(k, dvw, dp, 0, 1);
}

#define MULTIPLE_CASES 1

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)
#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}
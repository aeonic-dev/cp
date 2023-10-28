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

int solve(int k, vi &v, vi &dp, vec<bitset<1000>> &opts, bitset<1000> &opt, int next) {
    if (next >= k) return 0;

    auto &res = dp[next];
    if (res != -1) {
        rep(i, next, k) opt[i] = opts[next][i]; // bad
        return res;
    }

    auto optn(opt), optt(opt);
    optt[next] = true;

    auto notk = solve(k, v, dp, opts, optn, next + 1);
    auto take = v[next] + solve(k, v, dp, opts, optt, next + 2);

    if (take >= notk) {
        opts[next] = opt = optt;
        return res = take;
    }

    opts[next] = opt = optn;
    return res = notk;
}

int test = 1;

void solve() {
    int k;
    cin >> k;

    vi v(k);
    cin >> v;

    vi dp(k, -1);
    vec<bitset<1000>> opts(k);

    bitset<1000> opt;
    cout << "Case #" << test++ << ": " << solve(k, v, dp, opts, opt, 0) << " : ";
    rep(i, 0, k) if (opt[i]) cout << i << " ";
    cout << endl;
}

#define MULTIPLE_CASES 1

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)
#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}
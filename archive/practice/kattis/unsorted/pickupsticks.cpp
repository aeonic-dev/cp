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

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> above(n, 0);
    vec<vec<int>> below(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;

        above[b - 1]++;
        below[a - 1].pb(b - 1);
    }

    vec<int> removed;
    removed.reserve(n);

    queue<int> q;
    rep(i, 0, n) if (above[i] == 0) q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        removed.pb(cur);
        travis(i, below[cur]) if (--above[i] == 0) q.push(i);
    }

    if (removed.size() == n) travis(x, removed) cout << x + 1 << endl;
    else cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
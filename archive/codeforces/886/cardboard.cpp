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

inline ll find(ll num_sides, ll sum_sides, ll target, ll min, ll max) {
    ll w = min + (max - min) / 2;
    ll calc = w * 4 * (sum_sides + num_sides * w);

//    cout << "target: " << target << endl;
//    cout << "w: " << w << ", " << "calc: " << calc << endl;

    if (calc == target) return w;

    return (calc > target || calc < 0) ?
           find(num_sides, sum_sides, target, min, w) :
           find(num_sides, sum_sides, target, w, max);
}

inline ll find(ll num_sides, ll sum_sides, ll area, ll squarea) {
//    cout << area << ", " << squarea << endl;

    ll max_bound = (ll) sqrt((area - squarea) / num_sides) + 1;
    if (max_bound < 0) max_bound = (ll) sqrt(LONG_LONG_MAX) / num_sides;
    return find(num_sides, sum_sides, area - squarea, 0, max_bound);
}

void solve() {
    ll num_sides, c, s;
    cin >> num_sides >> c;

    ll sum_sides = 0;
    ll squarea = 0;
    rep(i, 0, num_sides) {
        cin >> s;
        sum_sides += s;
        squarea += s * s;
    }

    ll w = find(num_sides, sum_sides, c, squarea);
    cout << w << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}
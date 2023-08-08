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
typedef pair<ll, ll> pll;
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
// @formatter:on=

void solve() {
    int n;
    cin >> n;

    vec<int> a(n);
    cin >> a;

    ll cost = 0;
    bool carrying_red = false, need_red = false;
    rep(i, 0, n) {
        if (a[i] == 0) {
            if (need_red) {
                need_red = false;
                cost++; // The red we needed can't be gotten without buying it
            }

            if (carrying_red) carrying_red = false; // Use the red from left of here
            else need_red = true; // Buy it down the line
        } else if (a[i] == 1) {
            if (!carrying_red && !need_red) need_red = i > 0 && a[i - 1] == 0;
        } else { // a[i] == 2
            if (need_red) {
                need_red = false;
                carrying_red = true;

                cost++;
            }
        }
    }

    if (need_red) cost++;
    if (cost == 0) cost = 1;

    cout << cost << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // Unties cin from cout

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
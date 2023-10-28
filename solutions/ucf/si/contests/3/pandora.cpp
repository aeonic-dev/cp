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
#define trav(x, s) for (auto x: s)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

void factorize(vec<pi> &factors, int a, int b) {
    int i = 2;

    while (i * i <= a) {
        int e = 0;
        while (a % i == 0) {
            a /= i;
            e++;
        }

        if (e > 0) factors.eb(i, e * b);
        i++;
    }

    if (a>1) factors.eb(a, b);
}

ll MOD = 1000000007;

void solve() {
    int a, b;
    cin >> a >> b;

    if (a == 1 || b == 0) {
        cout << 1 << endl;
        return;
    }

    vec<pi> factors;
    factorize(factors, a, b);

    ll num = 1;
    trav(n, factors) {
        num *= ((n.second + 1) * (n.second + 2) / 2) % MOD;
        num %= MOD;
    }
    cout << num << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
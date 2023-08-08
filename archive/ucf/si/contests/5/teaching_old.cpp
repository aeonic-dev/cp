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
#define travis(x, s) for (auto &x: s)
#define numeric(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

const ll MAX = 1000;
ll facts[MAX + 1];

ll fact(ll n) {
    if (n <= 0 || n > MAX) return 1;
    if (facts[n] != -1) return facts[n];
    return n * fact(n - 1);
}

// Remember to add 1 for initial knowledge
ll num_taught(ll n, ll y) {
    if (n <= 1) return 1;
    if (y <= 1) return n;

    ll ret = n;
    rep(i, 2, y + 1) {
        ret += fact(n) / fact(n - i);
    }

    return ret;
}

void solve() {
    rep(i, 0, MAX + 1) cout << fact(i) << endl;

    ll t, y;
    cin >> t >> y;

    if (y == 1) {
        cout << t - 1 << endl;
        return;
    }

    for (ll n = y + 1; n <= MAX; n++) {
        ll num = 1 + num_taught(n, y);
        if (num >= t) {
            cout << n << endl;
            return;
        }
    }
}

int main() {
    memset(facts, -1, sizeof(facts));
    fact(MAX);
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
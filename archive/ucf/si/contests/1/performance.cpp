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
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<li> vli;
typedef vector<ll> vll;
typedef vector<pi> vpi;

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

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

void solve() {
    int x, y, tmp;
    li n, q;
    cin >> n >> q;

    vli frogs(n);
    rep(i, 0, n) cin >> frogs[i];

    rep(i, 0, q) {
        cin >> x >> y;
        tmp = frogs[x - 1];
        frogs[x - 1] = frogs[y - 1];
        frogs[y - 1] = tmp;
    }

    rep(i, 0, n) cout << frogs[i] << " ";
    cout << endl;
}

int main() {
//    freopen("milkorder.in", "r", stdin);
//    freopen("milkorder.out", "w", stdout);
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
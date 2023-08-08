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

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return a * b / __gcd(a, b);
}

void solve() {
    string s;
    cin >> s;

    vec<int> chars(26, 0);
    rep(i, 0, s.size()) chars[s[i] - 'a']++;

    if (chars['e' - 'a'] == 0) {
        cout << "impossibleeee" << endl;
        return;
    }

    int num = 0;
    rep(i, 0, 26) {
        if (i == 'e' - 'a') continue;
        if (chars[i] >= chars['e' - 'a']) num += chars[i] - chars['e' - 'a'] + 1;
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
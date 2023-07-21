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

void solve() {
    li n, cow_count = 0, m;
    int f, max_rate;

    cin >> n;

    map<li, li> cows{};
    vli rates{};

    rep(i, 0, n) {
        cin >> f >> m;

        if (cows.find(m) == cows.end()) {
            cows[m] = 0;
            rates.pb(m);
        }

        cows[m] += f;
        cow_count += f;
        if (m > max_rate) max_rate = m;
    }

    n = rates.size();
    sort(all(rates));

    vli pfx(n + 1, 0);
    vli rfx(n + 1, 0);
    rep(i, 0, n) {
        pfx[i + 1] = pfx[i] + cows[rates[i]] * 10;
        rfx[i + 1] = rfx[i] + cows[rates[n - i - 1]] * 10;
    }

    li a = -1, b = -1, a_count, b_count;
    for (int i = 0; i < n; i++) {
        if (a == -1 && pfx[i + 1] >= cow_count * 3) {
            a = rates[i];
            a_count = pfx[i + 1];

            if (b != -1) break;
        }

        if (b == -1 && rfx[i + 1] >= cow_count * 3) {
            b = rates[n - i - 1] - 1;
            b_count = rfx[i + 1];

            if (a != -1) break;
        }
    }

    if (a == -1 || b == -1) {
        cout << -1 << endl;
        return;
    }

    if ((cow_count * 10 - a_count - b_count) >= cow_count * 3) cout << a << " " << b << endl;
    else cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
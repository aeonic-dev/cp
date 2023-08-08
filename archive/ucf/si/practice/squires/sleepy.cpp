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

bool seen[(size_t) 10e5 + 1];

void solve() {
    memset(seen, false, sizeof(seen));

    int n;
    cin >> n;

    vi cows(n * 2, -1), moves;
    bool sorted = true;
    rep (i, 0, n) {
        cin >> cows[i];
        if (i > 0 && cows[i] < cows[i - 1]) sorted = false;
    }

    if (sorted) {
        cout << 0 << endl;
        return;
    }

    rep(i, 0, n) {
        if (seen[i]) break;

        if (cows[i] > cows[n + i - 1]) {
            cows[n + i] = cows[i];
            moves.pb(n - 1);
            continue;
        }

        bool done = true;
        rep(j, i, n) {
            if (seen[j]) break;

            if (cows[j] > cows[j + 1]) {
                done = false;
                break;
            }
        }
        seen[i] = true;
        if (done) break;

        int j;
        for (j = n + i - 1; j > i; j--) {
            if ((cows[j + 1] != -1 && cows[j] > cows[j + 1]) ||
                (cows[i] < cows[j + 1] && cows[i] > cows[j]))
                break;

            cows[j + 1] = cows[j];
        }
        cows[j + 1] = cows[i];
        moves.pb(j - i);
    }

    cout << moves.size() << endl;
    for (auto m: moves) cout << m << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/milk_time)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
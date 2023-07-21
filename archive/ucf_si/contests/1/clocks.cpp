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

string symbols[5] = {
        "OOOOO..O..OOOOOOOOOOO...OOOOOOOOOOOOOOOOOOOOOOOOOO..O..",
        "O...O..O......O....OO...OO....O........OO...OO...O..O..",
        "O...O..O..OOOOOOOOOOOOOOOOOOOOOOOOO....OOOOOOOOOOO.....",
        "O...O..O..O........O....O....OO...O....OO...O....O..O..",
        "OOOOO..O..OOOOOOOOOO....OOOOOOOOOOO....OOOOOOOOOOO..O..",
};

string get_row(char c, int row) {
    if (c == ':') return symbols[row].substr(50, 5);
    if (c >= '0' && c <= '9') return symbols[row].substr(5 * (c - '0'), 5);
    return ".....";
}

void solve() {
    string time_str;
    cin >> time_str;

    rep(i, 0, 5) {
        rep(j, 0, time_str.size()) {
            cout << get_row(time_str[j], i);
            if (j != time_str.size() - 1) cout << ".";
        }
        cout << endl;
    }

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
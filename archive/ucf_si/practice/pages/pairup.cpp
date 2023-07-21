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

struct cow_party {
    li num_cows;
    li milk_time;

    bool pop() {
        if (num_cows == 0) return false;

        num_cows--;
        return true;
    }

    inline bool operator<(const cow_party &rhs) const {
        return milk_time < rhs.milk_time;
    }
};

void solve() {
    int n;
    cin >> n;

    li num_cows, output;
    deque<cow_party> cows{};
    rep(i, 0, n) {
        cin >> num_cows >> output;
        cows.push_back({num_cows, output});
    }
    sort(all(cows));

    li max_time = -1;
    while (!cows.empty()) {
        if (!cows.front().pop()) {
            cows.pop_front();
            continue;
        }

        if (!cows.back().pop()) {
            cows.pop_back();
            continue;
        }

        max_time = max(max_time, cows.front().milk_time + cows.back().milk_time);
    }

    cout << max_time << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/milk_time)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
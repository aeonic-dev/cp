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

int N, M, K;

// Check if remaining cows from hierarchy can be placed in order from this position
bool check(vi order, vi &m) {
    // Cow to position map, initially populated by inverse of `order`
    vi pos(order.size(), -1);
    rep(i, 0, order.size()) if (order[i] != -1) pos[order[i]] = i;

    int m_i = 0;
    for (int i = 0; i < N && m_i < M; i++) {
        if (order[i] != -1) continue; // Skip occupied positions

        if (pos[m[m_i]] != -1) { // If the current cow in the hierarchy has already been placed in order
            if (pos[m[m_i]] < i) return false; // This cow has been placed earlier; hierarchy is broken
            i = pos[m[m_i]]; // Skip to the next position
            m_i ++;
        } else {
            // Normal placement
            order[i] = m[m_i];
            pos[m[m_i]] = i;
            m_i ++;
        }
    }

    return true;
}

void solve() {
    cin >> N >> M >> K;

    vi m(M), order(N, -1);
    rep(i, 0, M) cin >> m[i]; // Must be milked in this order
    rep(i, 0, K) {
        int cow, pos;
        cin >> cow >> pos;
        order[pos - 1] = cow - 1;

        if (cow == 1) {
            cout << pos << endl;
            return;
        }
    }

    rep(i, 0, N) {
        if (order[i] != -1) continue;

        order[i] = 0;
        if (check(order, m)) {
            cout << i + 1 << endl;
            return;
        }
        order[i] = -1;
    }
}

int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);

    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
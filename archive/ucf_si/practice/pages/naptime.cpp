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

struct point {
    int first;
    bool second;

    point(int first, bool second) : first(first), second(second) {}

    bool operator<(const point &rhs) const {
        if (first < rhs.first)return true;
        if (rhs.first < first)return false;

        return second && !rhs.second;
    }
};

void solve() {
    int n, s, e;
    cin >> n;

    multiset<point> pts{}; // true = start, false = end
    rep(i, 0, n) {
        cin >> s >> e;
        pts.insert(point(s, true));
        pts.insert(point(e, false));
    }

    int c = 0, start = -1, end = -1;
    vi naps{}, reviews{};
    for (auto &p: pts) {
        if (p.second) { // start
            if (c == 0) {
                if (end != -1) {
                    if (end >= p.first) {
                        end = -1;
                        continue;
                    }

                    reviews.pb(p.first - end);
                    start = end;
                    end = -1;
                }

                if (start != -1 && start < p.first) naps.pb(p.first - start);
                start = p.first;
            }
            c++;
        } else { // end
            c--;
            if (c == 0) end = p.first;
        }
    }

    if (end != -1) reviews.pb(end - start);

    cout << naps.size();
    rep(i, 0, naps.size()) cout << " " << naps[i];
    cout << endl;
    rep(i, 0, reviews.size()) cout << reviews[i] << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/milk_time)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
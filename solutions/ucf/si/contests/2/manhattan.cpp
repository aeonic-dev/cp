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
#define THANKS void GIVE_ME_A_SEMICOLON() // requires semicolon when calling b macro

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

li distance(li x1, li y1, li x2, li y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

struct pt {
    int index, x, y;

    pt() : index(-1), x(-1), y(-1) {}

    pt(int x, int y) : x(x), y(y) {}

    pt(int index, int x, int y) : index(index), x(x), y(y) {}

    li distance_to(pt other) const;

    bool operator<(const pt &other) const;
};

pt b, e;

li pt::distance_to(pt other) const {
    return distance(x, y, other.x, other.y);
}

bool pt::operator<(const pt &other) const {
    li tb = this->distance_to(b);
    li te = this->distance_to(e);
    li ob = other.distance_to(b);
    li oe = other.distance_to(e);

    li d1 = max(tb, te);
    li d2 = max(ob, oe);
    if (d1 < d2) return true;
    if (d1 > d2) return false;

    li d3 = abs(tb - te);
    li d4 = abs(ob - oe);
    if (d3 < d4) return true;
    if (d3 > d4) return false;

    return index < other.index;
}

void solve() {
    int n, bx, by, ex, ey, x, y;
    cin >> n >> bx >> by >> ex >> ey;

    b = pt(bx, by);
    e = pt(ex, ey);

    vec<pt> pts(n);
    rep(i, 0, n) {
        cin >> x >> y;
        pts[i] = pt(i, x, y);
    }
    sort(all(pts));

    rep(i, 0, n) cout << pts[i].x << " " << pts[i].y << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
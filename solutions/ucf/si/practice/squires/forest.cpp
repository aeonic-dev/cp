// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

//#pragma GCC target("avx2")
//#include <nmmintrin.h>

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

struct pt {
    double x, y;

    pt() : x(0), y(0) {}

    pt(double x, double y) : x(x), y(y) {}

    double distance(pt p) const {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }

    pt operator+(pt p) const {
        return {x + p.x, y + p.y};
    }

    pt operator-(pt p) const {
        return {x - p.x, y - p.y};
    }

    pt operator*(double d) const {
        return {x * d, y * d};
    }

    pt operator/(double d) const {
        return {x / d, y / d};
    }

    double dot(pt p) const {
        return x * p.x + y * p.y;
    }

    double cross(pt p) const {
        return x * p.y - y * p.x;
    }

    double cross(pt p, pt q) const {
        return (p - *this).cross(q - *this);
    }

    double norm() const {
        return x * x + y * y;
    }

    double mag() const {
        return sqrt(norm());
    }

    bool operator==(const pt &p) const {
        return x == p.x && y == p.y;
    }
};

double area(const pt &a, const pt &b, const pt &c) {
    return abs((b - a).cross(c - a)) / 2;
}

void solve() {
    int n, r;
    cin >> n >> r;

    pt pivot;
    vec<pt> pts(n);
    rep(i, 0, n) cin >> pts[i].x >> pts[i].y;

    pts.erase(unique(all(pts)), pts.end());
    sort(all(pts), [](pt a, pt b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    if (pts.size() == 1) {
        cout << 2 * M_PI * r << " " << M_PI * r * r << endl;
        return;
    }

    if (pts.size() == 2) {
        cout <<
             2 * M_PI * r + 2 * pts[0].distance(pts[1]) << " " <<
             M_PI * r * r + 2 * pts[0].distance(pts[1]) * r << endl;
        return;
    }

    pivot = pts[0];
    sort(pts.begin() + 1, pts.end(), [&](pt a, pt b) {
        pt p1 = a - pivot, p2 = b - pivot;
        double cross = p1.cross(p2);
        return cross == 0 ? p1.norm() < p2.norm() : cross > 0;
    });

    vec<pt> hull{pivot};
    rep(i, 1, n) {
        while (hull.size() > 1 && hull[hull.size() - 2].cross(hull[hull.size() - 1], pts[i]) < 0) {
            hull.pop_back();
        }
        hull.pb(pts[i]);
    }

    double perimeter = 2 * M_PI * r, area = M_PI * r * r;
    rep(i, 0, hull.size()) {
        pt p1 = hull[i], p2 = hull[(i + 1) % hull.size()], p3 = hull[(i + 2) % hull.size()];

        double d = p1.distance(p2);
        perimeter += d;
        area += d * r;

        if (i != 0 && i < hull.size() - 1) area += ::area(pivot, p1, p2);
//        pt u = p2 - p1, v = p3 - p2;
//        double theta = acos(u.dot(v) / (sqrt(u.norm()) * sqrt(v.norm())));
//        perimeter += theta * r;
//        area += r * r * theta / 2;
    }

    cout << perimeter << " " << area << endl;
}

int main() {
    cout << setprecision(2) << fixed;
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    solve();
}
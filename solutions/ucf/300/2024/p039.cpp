#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrtl((ld) dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2l(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(ld a) const {
        return P(x * cosl(a) - y * sinl(a), x * sinl(a) + y * cosl(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ld> P;
const ld eps = 1e-6;
const ld pi = acos(-1);

// 1/0/-1 : left/on/right of a->b
template<class P>
int sideOf(const P &s, const P &e, const P &p) {
    auto a = (e - s).cross(p - s);
    ld l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}

/**
 * Finds the external tangents of two circles, or internal if r2 is negated.
 * Can return 0, 1, or 2 tangents -- 0 if one circle contains the other (or
 * overlaps it, in the internal case, or if the circles are the same); 1 if
 * the circles are tangent to each other (in which case .first = .second and
 * the tangent line is perpendicular to the line between the centers).
 * .first, .second give the tangency points at circles 1 and 2 respectively.
 */
template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
    P d = c2 - c1;
    double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) return {};
    vector<pair<P, P>> out;
    for (ld sign : {-1, 1}) {
        P v = (d * dr + d.perp() * sqrtl(h2) * sign) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    if (h2 == 0) out.pop_back();
    return out;
}

// duhh
template<class P>
vector<P> convexHull(vector<P> poly) {
    int n = sz(poly);
    vector<P> hull(n + 1);
    sort(all(poly));
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && hull[k - 2].cross(hull[k - 1], poly[i]) <= 0) k--;
        hull[k++] = poly[i];
    }
    for (int i = n - 1, t = k + 1; i > 0; i--) {
        while (k >= t && hull[k - 2].cross(hull[k - 1], poly[i - 1]) <= 0) k--;
        hull[k++] = poly[i - 1];
    }
    hull.resize(k - 1);
    return hull;
}

#if dbg
#include "geo.h"
#endif
void solve() {
    int n;
    cin >> n;

    vector<pair<P, ld>> circles(n);
    // vector<set<pair<ld, bool>>> inters(n);
    map<P, int> on_circle;
    for (auto &[p, r] : circles) cin >> p.x >> p.y >> r;

    if (n == 1) return void(
            cout << fixed << setprecision(10)
                 << 2 * pi * circles[0].second << '\n');

    vector<P> pts;
    rep(i, 0, n) {
        auto &&[a, r_a] = circles[i];
        rep(j, i + 1, n) {
            auto &&[b, r_b] = circles[j];
            auto tans = tangents(a, r_a, b, r_b);

            if (sideOf(a, b, tans[0].first) >= 0)
                swap(tans[0], tans[1]); // tans[0] is the left one

            pts.push_back(tans[0].first);
            pts.push_back(tans[1].first);
            pts.push_back(tans[0].second);
            pts.push_back(tans[1].second);

            on_circle[tans[0].first] = i;
            on_circle[tans[1].first] = i;
            on_circle[tans[0].second] = j;
            on_circle[tans[1].second] = j;
        }
    }
    sort(all(pts));
    pts.erase(unique(all(pts)), pts.end());
    auto hull = convexHull(pts);

#if dbg
    GD_INIT("vis.html");
    for (auto &[p, r] : circles)
        GD_CIRCLE(p.x, p.y, r, "black");
#endif

    // length of segments
    ld res = 0;
    rep(i, 0, sz(hull)) {
        P a = hull[i], b = hull[(i + 1) % sz(hull)];
#if dbg
        GD_POINT(a.x, a.y, "red");
#endif
        if (on_circle[a] != on_circle[b]) {
            // segment between two circles
            res += (a - b).dist();
#if dbg
            GD_SEGMENT(a.x, a.y, b.x, b.y, "red");
#endif
            continue;
        }

        // arc on a circle
        auto &&[p, r] = circles[on_circle[a]];
        P u = (a - p).unit(), v = (b - p).unit();
        ld theta = atan2l(u.cross(v), u.dot(v));
        if (theta < 0) theta += 2 * pi;
#if dbg
        GD_ARC(p.x, p.y, r, u.angle(), v.angle(), "red") << "theta = " << theta;
#endif

        res += r * theta;
    }
    cout << fixed << setprecision(10) << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

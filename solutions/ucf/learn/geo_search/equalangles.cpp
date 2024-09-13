#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long      ll;
typedef long double    ld;
typedef pair<int, int> pii;
typedef vector<int>    vi;

template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
    typedef Point P;
    T             x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    static Point polar(ld theta, T dist = 1) {
        return {
                cos(theta) * dist,
                sin(theta) * dist
        };
    }

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

    double dist() const { return sqrt((double) dist2()); }

    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }

    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }

    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend ostream &operator<<(ostream &os, P p) {
        return os << p.x << " " << p.y;
    }
};

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

typedef Point<ld> P;

ld angle(P a, P b) {
    return abs(acos(a.dot(b) / (a.dist() * b.dist())));
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
    auto a = (e-s).cross(p-s);
    double l = (e-s).dist()*eps;
    return (a > l) - (a < -l);
}

pair<ld, P> dist1(P &a, P &b, P &c, ld theta) {
    P d = a + P::polar((b - a).angle() + theta),
      e = b + P::polar((c - b).angle() + theta),
      f = c + P::polar((a - c).angle() + theta);

    auto u = lineInter(a, d, b, e),
         v = lineInter(a, d, c, f);

    return {(v.second - u.second).dist(), u.second};
}

pair<ld, P> dist2(P &a, P &b, P &c, ld theta) {
    P d = a + P::polar((c - a).angle() - theta),
      e = b + P::polar((a - b).angle() - theta),
      f = c + P::polar((b - c).angle() - theta);

    auto u = lineInter(a, d, b, e),
         v = lineInter(a, d, c, f);

    return {(v.second - u.second).dist(), u.second};
}

void solve() {
    P a, b, c, p, q;
    while (1) {
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        if (a.dist2() == 0 && b.dist2() == 0 && c.dist2() == 0) return;

        if (sideOf(a, b, c) < 0) swap(a, c);
        ld min_angle = min(angle(a, b), min(angle(b, c), angle(c, a)));

        ld lo = 0, hi = min_angle;
        rep(i, 0, 200) {
            ld   m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            auto d1 = dist1(a, b, c, m1),
                 d2 = dist1(a, b, c, m2);

            if (d1.first > d2.first) lo = m1;
            else hi = m2;

            p = d1.second;
        }

        lo = 0, hi = min_angle;
        rep(i, 0, 200) {
            ld   m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            auto d1 = dist2(a, b, c, m1),
                 d2 = dist2(a, b, c, m2);

            if (d1.first > d2.first) lo = m1;
            else hi = m2;

            q = d1.second;
        }

        cout << setprecision(2) << fixed;
        cout << p << " " << q << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

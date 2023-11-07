#include <bits/stdc++.h>

using namespace std;

#define vec vector
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
    typedef Point P;
    T x, y;

    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}

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
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P &s, const P &e, const P &p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}

typedef Point<ld> P;

pair<P, P> find_h_g(P a, P b, P c, ld area_tri, ld lo, ld hi) {
    ld mid = (lo + hi) / 2;

    P h = a + (c - a) * mid;
    ld area_par = abs((h - a).cross(b - a));
    if (abs(area_par - area_tri) < 1e-6) return {h, b + (h - a)};

    if (area_par < area_tri) return find_h_g(a, b, c, area_tri, mid, hi);
    return find_h_g(a, b, c, area_tri, lo, mid);
}

void solve() {
    while (1) {
        P a, b, c, d, e, f;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y >> e.x >> e.y >> f.x >> f.y;

        if (a.dist2() == b.dist2() &&
            b.dist2() == c.dist2() &&
            c.dist2() == d.dist2() &&
            d.dist2() == e.dist2() &&
            e.dist2() == f.dist2() &&
            f.dist2() == 0)
            return;

        // area of triangle DEF
        ld area_tri = abs((e - d).cross(f - d)) / 2;
        auto res = find_h_g(a, b, c, area_tri, 0, 1);
        auto h = res.first, g = res.second;
        cout << setprecision(3) << fixed;
        cout << g.x << " " << g.y << " " << h.x << " " << h.y << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    solve();

    return 0;
}
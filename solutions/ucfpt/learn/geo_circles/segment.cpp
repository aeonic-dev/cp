#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
const double pi = acos(-1);

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

    ld dist() const { return sqrt((ld) dist2()); }

    ld dist(P p) const {
        return (p - *this).dist();
    }

    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2(y, x); }

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
vector<P> circleLine(P c, double r, P a, P b) {
    P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
    double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p - h, p + h};
}

const ld eps = 1e-6;
template<class P> bool onSegment(P s, P e, P p) {
    return abs(p.cross(s, e)) < eps && (s - p).dot(e - p) <= eps;
}

typedef Point<ld> P;

void solve() {
    P c, s, e;
    double r;

    while (1) {
        if (scanf("%Lf", &c.x) == EOF) break;
        cin >> c.y >> r >> s.x >> s.y >> e.x >> e.y;

        auto res = circleLine(c, r, s, e);
        for (auto p: res) {
            if (onSegment(s, e, p)) {
                cout << "The line segment intersects the circle.\n";
                goto next;
            }
        }

        cout << "The line segment does not intersect the circle.\n";
        next:;
    }
}

int main() {
//    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

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

typedef Point<ld> P;

bool circleInter(P a, P b, ld r1, ld r2, pair<ld, ld> &out) {
    ld d = a.dist(b);
    if (d >= r1 + r2) return false;

    out.first = 2 * acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    out.second = 2 * acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
    return true;
}

ld angle(ld d, ld r) {
    return 2 * asin(d / (2 * r));
}

void solve() {
    int n;
    cin >> n;

    P c_last, c;
    ld r_last, r = -1, area = 0;
    rep(i, 0, n) {
        c_last = c;
        r_last = r;

        cin >> c.x >> c.y >> r;
        area += M_PI * r * r;

        if (r_last == -1) continue;

        pair<ld, ld> res;
        if (circleInter(c, c_last, r, r_last, res)) {
            ld theta1 = res.first;
            ld theta2 = res.second;

            area -= (r * r / 2) * (theta1 - sin(theta1));
            area -= (r_last * r_last / 2) * (theta2 - sin(theta2));
        }
    }

    cout << area << "\n\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    cout << setprecision(2) << fixed;
    rep(i, 0, t) {
        cout << "Set #" << i + 1 << ": ";
        solve();
    }

    return 0;
}

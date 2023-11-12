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

    double dist(P p) const {
        return (p - *this).dist();
    }

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
P lineProj(P a, P b, P p, bool refl = false) {
    P v = b - a;
    return p - v.perp() * (1 + refl) * v.cross(p - a) / v.dist2();
}

typedef Point<ld> P;

ld segDist(P &s, P &e, P &p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max((ld) 0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}

void solve() {
    P A, B, C;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

    // AB will = hypotenuse
    ld AB = A.dist(B), BC = B.dist(C), AC = A.dist(C);
    ld max = ::max(AB, ::max(BC, AC));
    if (max == BC) {
        swap(A, B);
        swap(B, C);
        swap(AB, BC);
        swap(BC, AC);
    } else if (max == AC) {
        swap(B, C);
        swap(AB, AC);
    }

    P M = lineProj(A, B, C); // point on AB projected down from C
    ld h = segDist(A, B, C); // height
    ld AM = A.dist(M), BM = B.dist(M); // split base lengths

    // if m is centered, that's our balance point
    if (abs(AM - BM) < 1e-6) {
        cout << M << endl;
        return;
    }

    ld left = AM * h / 2;
    ld right = BM * h / 2;

    if (AM > BM) {
        // balance point is on the left side
        ld v = sqrt((right + left) / (2 * left)); // 0-1 A -> M
        cout << (A + (M - A) * v) << endl;
    } else {
        // balance point is on the right side
        ld v = sqrt((right + left) / (2 * right)); // 0-1 B -> M
        cout << (B + (M - B) * v) << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    cout << setprecision(2) << fixed;
    rep(i, 0, t) {
        cout << "Triangle #" << i + 1 << " Balance Point: ";
        solve();
    }

    return 0;
}

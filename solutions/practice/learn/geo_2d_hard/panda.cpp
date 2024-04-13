#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
#define sz(x) (x).size()
typedef long long ll;

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

const double eps = 1e-8, inf = 1e8;
typedef Point<double> P;

struct HalfPlane {
    P s, e, d;
    HalfPlane(P s = P(), P e = P()) : s(s), e(e), d(e - s) {}
    bool contains(P p) { return d.cross(p - s) > -eps; }
    bool operator<(HalfPlane hp) const {
        if (abs(d.x) < eps && abs(hp.d.x) < eps)
            return d.y > 0 && hp.d.y < 0;
        bool side = d.x < eps || (abs(d.x) <= eps && d.y > 0);
        bool sideHp = hp.d.x < eps || (abs(hp.d.x) <= eps && hp.d.y > 0);
        if (side != sideHp) return side;
        return d.cross(hp.d) > 0;
    }
    P inter(HalfPlane hp) {
        auto p = hp.s.cross(e, hp.e), q = hp.s.cross(hp.e, s);
        return (s * p + e * q) / d.cross(hp.d);
    }
};

vector<P> hpIntersection(vector<HalfPlane> hps) {
    sort(all(hps));
    int n = sz(hps), l = 1, r = 0;
    vector<HalfPlane> dq(n + 1);
    rep(i, 0, n) {
        while (l < r && !hps[i].contains(dq[r].inter(dq[r - 1]))) r--;
        while (l < r && !hps[i].contains(dq[l].inter(dq[l + 1]))) l++;
        dq[++r] = hps[i];
        if (l < r && abs(dq[r].d.cross(dq[r - 1].d)) < eps) {
            if (dq[r].d.dot(dq[r - 1].d) < 0) return {};
            r--;
            if (dq[r].contains(hps[i].s)) dq[r] = hps[i];
        }
    }
    while (l < r - 1 && !dq[l].contains(dq[r].inter(dq[r - 1]))) r--;
    while (l < r - 1 && !dq[r].contains(dq[l].inter(dq[l + 1]))) l++;
    if (l > r - 2) return {};
    vector<P> poly;
    rep(i, l, r)poly.push_back(dq[i].inter(dq[i + 1]));
    poly.push_back(dq[r].inter(dq[l]));
    return poly;
}

template<class P>
bool onSeg(P s, P e, P p) {
    return abs(s.cross(e, p)) < eps && (s - p).dot(e - p) < eps;
}

template<class P>
int sideOf(P s, P e, P p) {
    auto cp = s.cross(e, p);
    return (cp > eps) - (cp < -eps);
}

template<class P>
bool doSegInter(P s1, P e1, P s2, P e2) {
    return sideOf(s1, e1, s2) != sideOf(s1, e1, e2) &&
           sideOf(s2, e2, s1) != sideOf(s2, e2, e1);
}

template<class P>
P lineInter(P s1, P e1, P s2, P e2) {
    auto det = -(e1 - s1).cross(e2 - s2);
    if (abs(det) < eps) return P(inf, inf);
    auto t = (e2 - s2).cross(s2 - s1) / det;
    return s1 + (e1 - s1) * t;
}

template<class P>
vector<P> segInter(P s1, P e1, P s2, P e2) {
    if (doSegInter(s1, e1, s2, e2)) return {lineInter(s1, e1, s2, e2)};
    set < P > seg;
    if (onSeg(s1, e1, s2)) seg.insert(s2);
    if (onSeg(s1, e1, e2)) seg.insert(e2);
    if (onSeg(s2, e2, s1)) seg.insert(s1);
    if (onSeg(s2, e2, e1)) seg.insert(e1);
    return {all(seg)};
}

template<class P>
int inPoly(vector<P> poly, P p) {
    bool good = false;
    int n = sz(poly);
    auto crosses = [](P s, P e, P p) {
        return ((e.y >= p.y) - (s.y >= p.y)) * p.cross(s, e) > 0;
    };
    for (int i = 0; i < n; i++) {
        if (onSeg(poly[i], poly[(i + 1) % n], p)) return 2;
        good ^= crosses(poly[i], poly[(i + 1) % n], p);
    }
    return good;
}

void solve() {
    int n;
    cin >> n;
    vec<P> pts(n);
    rep(i, 0, n) cin >> pts[i].x >> pts[i].y;

    vec<P> bbpts{P(-inf, -inf), P(inf, -inf), P(inf, inf), P(-inf, inf)};
    vec<HalfPlane> bb;
    rep(i, 0, 4) bb.emplace_back(bbpts[i], bbpts[(i + 1) % 4]);

    vec<vec<HalfPlane>> hps(n, bb);
    rep(i, 0, n) {
        rep(j, i + 1, n) {
            P &u = pts[i], &v = pts[j], vu = v - u;
            P mp = u + vu * .5, perp = vu.perp();
            hps[i].emplace_back(mp, mp + perp);
            hps[j].emplace_back(mp, mp - perp);
        }
    }

    double max = 0;
    rep(i, 0, n) {
        P &p = pts[i];
        auto cell = hpIntersection(hps[i]);
        int m = sz(cell);
        rep(j, 0, m) {
            P &u = cell[j], &v = cell[(j + 1) % m];
            if (inPoly(pts, u)) max = ::max(max, (u - p).dist());

            rep(k, 0, n) {
                P &q = pts[k], &r = pts[(k + 1) % n];
                for (auto inter : segInter(u, v, q, r)) {
                    max = ::max(max, (inter - p).dist());
                }
            }
        }
    }
    cout << max << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(8) << fixed;

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

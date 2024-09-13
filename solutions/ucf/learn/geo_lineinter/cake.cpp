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
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

typedef Point<ld> P;

void solve() {
    int n, y;
    cin >> n >> y;

    vec<P> pts(n);
    rep(i, 0, n) cin >> pts[i].x >> pts[i].y;
    P s = P(-2000, y), e = P(2000, y);

    P pivot;
    vec<P> top, bot;
    rep(i, 0, n) {
        P a = pts[i], b = pts[(i + 1) % n];
        (a.y < y ? bot : top).push_back(a);

        // lineInter gives false positives
        if ((a.y < y) == (b.y < y)) continue;

        auto res = lineInter(s, e, a, b);
        if (res.first == 1) {
            pivot = res.second; // doesn't matter which we use as pivot
            top.push_back(res.second);
            bot.push_back(res.second);
        }
    }

    sort(all(top), [&](P a, P b) {
        P p1 = a - pivot, p2 = b - pivot;
        ld crs = p1.cross(p2);
        return crs == 0 ? p1.dist() < p2.dist() : crs > 0;
    });
    sort(all(bot), [&](P a, P b) {
        P p1 = a - pivot, p2 = b - pivot;
        ld crs = p1.cross(p2);
        return crs == 0 ? p1.dist() < p2.dist() : crs > 0;
    });

    ld pt = 0, pb = 0;
    rep(i, 0, top.size()) {
        P a = top[i], b = top[(i + 1) % top.size()];
        pt += a.dist(b);
    }

    rep(i, 0, bot.size()) {
        P a = bot[i], b = bot[(i + 1) % bot.size()];
        pb += a.dist(b);
    }

    if (pt > pb) swap(pt, pb);
    cout << pt << " " << pb << "\n\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    cout << setprecision(3) << fixed;
    rep(i, 0, t) {
        cout << "Case #" << i + 1 << ": ";
        solve();
    }

    return 0;
}

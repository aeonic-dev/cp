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

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
    P ab = b - a, p = a + ab * (c - a).dot(ab) / ab.dist2();
    double s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p - h, p + h};
}

typedef Point<ld> P;

template<typename n_t>
void unset_bit(n_t &mask, int i) {
    mask &= ~(1 << i);
}

template<typename n_t>
void set_bit(n_t &mask, int i, bool val = true) {
    if (val) mask |= (1 << i);
    else unset_bit(mask, i);
}

template<typename n_t>
bool get_bit(n_t &mask, int i) {
    return (mask >> i) & 1;
}

void solve() {
    int n, m, r; // candles, slices, r
    cin >> n >> m >> r;

    vec<P> candles(n);
    rep(i, 0, n) {
        cin >> candles[i].x >> candles[i].y;
    }

    vec<pair<P, P>> lines(m);
    rep(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;

        ld slope;// = -a / (ld) b;
        if (a != 0 && (b == 0 || (slope = -a / (ld) b, (slope == 0 || slope > 1 || slope < -1)))) {
            // solve for x at y=1000,-1000
            lines[i] = {
                    P(
                            -(b * -1000 + c) / (ld) a,
                            -1000
                    ),
                    P(
                            -(b * 1000 + c) / (ld) a,
                            1000
                    )
            };
        } else {
            // solve for y at x=1000,-1000
            lines[i] = {
                    P(
                            -1000,
                            -(a * -1000 + c) / (ld) b
                    ),
                    P(
                            1000,
                            -(a * 1000 + c) / (ld) b
                    )
            };
        }
    }

    int edges = 0;
    vec<P> pts, pts_r;
    rep(i, 0, m) {
        auto &u = lines[i];

        vec<P> pts_i;
        rep(j, 0, m) {
            if (i == j) continue;

            auto &v = lines[j];
            auto res = lineInter(u.first, u.second, v.first, v.second);

            if (res.first == 1) {
                if (res.second.dist() > r) continue;

                for (auto &p: pts_i) {
                    if ((p - res.second).dist() < 1e-4) goto end;
                }
                pts_i.push_back(res.second);

                for (auto &p: pts) {
                    if ((p - res.second).dist() < 1e-4) goto end;
                }
                pts.push_back(res.second);
                end:;
            }
        }

        // circle intersection points
        auto res = circleLine(P(0, 0), r, u.first, u.second);

        for (auto &np: res) {
            for (auto &p: pts_i) {
                if ((p - np).dist() < 1e-4) goto end2;
            }
            pts_i.push_back(np);

            for (auto &p: pts_r) {
                if ((p - np).dist() < 1e-4) goto end2;
            }
            pts_r.push_back(np);

            for (auto &p: pts) {
                if ((p - np).dist() < 1e-4) goto end2;
            }
            pts.push_back(np);
            end2:;
        }

        edges += sz(pts_i) - 1;
    }

    edges += sz(pts_r);
    int f = 1 - (sz(pts) - edges);

    if (n != f) {
        cout << "no\n";
        return;
    }

    set<ll> sides; // set of side bitsets
    for (auto &p: candles) {
        ll mask = 0;
        rep(i, 0, m) {
            auto &ln = lines[i];
            set_bit(mask, i, sideOf(ln.first, ln.second, p, 1e-4) == 1);
        }

        if (sides.count(mask)) {
            cout << "no\n";
            return;
        }
        sides.insert(mask);
    }

    cout << "yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    solve();

    return 0;
}
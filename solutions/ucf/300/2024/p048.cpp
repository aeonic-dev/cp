#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
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
    ld dist() const { return sqrtl((ld) dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
const ld inf = 1e18;
const ld eps = 1e-8;
typedef Point<ld> P;

template<class P>
int sideOf(P s, P e, P p) {
    auto cp = s.cross(e, p);
    return (cp > 0) - (cp < 0);
}

template<class P>
bool doSegInter(P s1, P e1, P s2, P e2) {
    return sideOf(s1, e1, s2) != sideOf(s1, e1, e2) && sideOf(s2, e2, s1) != sideOf(s2, e2, e1);
}

// 0 = no intersection, 1 = segments intersect, -1 = coincide or share an endpoint
int segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);

    // c1 = oc
    // c2 = od
    // c3 = ob
    // c4 = oa

    if (sgn(oa) * sgn(ob) > 0 || sgn(oc) * sgn(od) > 0) return 0; // no intersection
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return 1; // intersection

    return -1; // coincide or share an endpoint
}

template<class P>
bool onSegment(P s, P e, P p) {
    return abs(s.cross(e, p)) < eps && (s - p).dot(e - p) < eps;
}

template<class P>
int inPoly(vector<P> poly, P p) {
    bool good = false;
    int n = sz(poly);
    auto crosses = [](P s, P e, P p) {
        return ((e.y >= p.y) - (s.y >= p.y)) * p.cross(s, e) > 0;
    };
    for (int i = 0; i < n; i++) {
        if (onSegment(poly[i], poly[(i + 1) % n], p)) return 2;
        good ^= crosses(poly[i], poly[(i + 1) % n], p);
    }
    return good;
}

// #include "geo.h"
void solve() {
    int n, m;
    cin >> n >> m;

    vector<P> pol(n), pts(m), old_pts(n + m), all_pts;
    for (auto &[x, y] : pol) cin >> x >> y;
    for (auto &[x, y] : pts) cin >> x >> y;
    copy(all(pol), begin(old_pts));
    copy(all(pts), begin(old_pts) + n);

    // sort everything
    rep(i, 0, n) {
        P u = pol[i], v = pol[(i + 1) % n];
        vector<P> lin;

        for (P p : old_pts) {
            if (onSegment(u, v, p)) lin.push_back(p);
        }
        old_pts.erase(
                remove_if(all(old_pts), [&](P p) {
                    return count(all(lin), p);
                }),
                end(old_pts));

        sort(all(lin), [&](P a, P b) {
            return (a - u).dist2() < (b - u).dist2();
        });
        all_pts.insert(end(all_pts), all(lin));
    }
    all_pts.erase(unique(all(all_pts)), end(all_pts));
    int tot = sz(all_pts);

    // GD_INIT("vis.html");
    // rep(i, 0, tot) {
    //     P u = all_pts[i], v = all_pts[(i + 1) % tot];
    //     if (count(all(pts), u)) GD_POINT(u.x, u.y, "black");
    //     GD_SEGMENT(u.x, u.y, v.x, v.y, "black");
    // }
    // GD_PAUSE();

    vector<vector<pair<int, ld>>> adj(tot);
    auto check = [&](int i, int j) -> bool {
        P a = all_pts[i], b = all_pts[j];
        set<P> s{a, b};

        // GD_LAYER();
        // GD_SEGMENT(a.x, a.y, b.x, b.y, "orange bold");

        // check if we intersect any edges (that are not adjacent to a or b)
        rep(k, 0, n) {
            // if (k == i || k == j || (k + 1) % n == i || (k + 1) % n == j) continue;
            P c = pol[k], d = pol[(k + 1) % n];
            // GD_SEGMENT(c.x, c.y, d.x, d.y, "orange");

            // check for intersection
            int inter = segInter(a, b, c, d);
            if (inter > 0) {
                return false;
                // GD_SEGMENT(a.x, a.y, b.x, b.y, "red bold");
                // GD_SEGMENT(c.x, c.y, d.x, d.y, "red bold");
            }
            if (inter < 0) {
                if (onSegment(a, b, c)) s.insert(c);
                if (onSegment(a, b, d)) s.insert(d);
                if (onSegment(c, d, a)) s.insert(a);
                if (onSegment(c, d, b)) s.insert(b);
            }
        }

        // check if the edge is inside the polygon
        vector<P> inters(sz(s));
        copy(all(s), begin(inters));

        rep(k, 0, sz(inters)) {
            P u = inters[k], v = inters[(k + 1) % sz(inters)];
            P m = (u + v) / 2.l;
            if (!inPoly(pol, m)) return false;
        }

        // GD_SEGMENT(a.x, a.y, b.x, b.y, "green");
        return true;
    };

    vector<vector<ld>> dist(tot, vector<ld>(tot, 1e18));
    rep(i, 0, tot) dist[i][i] = 0;
    rep(i, 0, tot) rep(j, i + 1, tot) if (check(i, j)) {
            dist[i][j] = dist[j][i] = (all_pts[i] - all_pts[j]).dist();
            // GD_SEGMENT(all_pts[i].x, all_pts[i].y, all_pts[j].x, all_pts[j].y, "green") << "i = " << i << ", j = " << j;
            // GD_PAUSE();
    }
    rep(h, 0, tot) rep(i, 0, tot) rep(j, 0, tot)
            dist[i][j] = min(
                    dist[i][j],
                    dist[i][h] + dist[h][j]);

    // // print dist
    // cout << "\ndist:\n";
    // rep(i, 0, k) {
    //     cout << i << ": {\n";
    //     rep(j, 0, k) cout << "\t-> " << j << " = " << dist[i][j] << "\n";
    //     cout << "}\n";
    // }

    vector<int> ord;
    rep(i, 0, m) {
        rep(j, 0, tot) {
            if (all_pts[j] == pts[i]) {
                ord.push_back(j);
                break;
            }
        }
    }
    sort(all(ord));
    assert(sz(ord) == m);

    // GD_PAUSE();
    ld res = 0;
    rep(i, 0, m) {
        int u = ord[i], v = ord[(i + 1) % m];
        res += dist[u][v];
        // GD_SEGMENT(all_pts[u].x, all_pts[u].y, all_pts[v].x, all_pts[v].y, "red bold");
    }
    cout << setprecision(10) << fixed << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

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
    bool operator<(P p) const { return tie(y, x) < tie(p.y, p.x); }
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
typedef Point<ll> P;

struct dsu {
    vi par, siz;
    dsu(int n) {
        siz = par = vi(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int a) {
        if (par[a] != a) par[a] = find(par[a]);
        return par[a];
    }
    bool join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
        return true;
    }
};

void solve() {
    int n;
    while (cin >> n, n) {
        vector<P> pts(n);
        for (auto &[x, y] : pts) cin >> x >> y;
        sort(all(pts));

        // {max y, d, i, j}
        vector<tuple<ll, double, int, int>> edges;
        rep(i, 0, n) {
            P a = pts[i];
            rep(j, i + 1, n) {
                P b = pts[j];
                edges.emplace_back(max(a.y, b.y), (b - a).dist(), i, j);
            }
        }
        sort(all(edges));

        ld res = 0;
        dsu ds(n);
        for (auto [_, w, u, v] : edges) {
            if (!ds.join(u, v)) continue;
            res += w;
        }
        cout << fixed << setprecision(2) << res << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

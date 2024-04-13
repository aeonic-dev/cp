#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
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

typedef Point<int> P;
const P zero{0, 0};

void solve() {
    int n;
    cin >> n, n--;
    vector<P> pts(n);
    for (auto &[x, y] : pts) cin >> x >> y;
    sort(all(pts), [](P a, P b) { return a.angle() < b.angle(); });
    
    // get heights (use tallest for 0,0)
    vi hts(n + 1);
    for (int &x : hts) cin >> x;
    sort(all(hts), greater<>());
    int z_m = hts[0];
    hts = {1 + all(hts)};
    
    // assign heights to points
    vi inds(n);
    iota(all(inds), 0);
    auto quad2A = [&](int i) -> int {
        P a = pts[(i + n - 1) % n], b = pts[i], c = pts[(i + 1) % n];
        return abs(a.cross(b)) + abs(b.cross(c));
    };
    sort(all(inds), [&](int i, int j) {
        return quad2A(i) > quad2A(j);
    });
    vi zs(n);
    rep(i, 0, n) zs[inds[i]] = hts[i];
    
    // get volume
    double res = 0;
    auto vol = [&](P a, int z_a, P b, int z_b) -> double {
        double z_avg = (z_m + z_a + z_b) / 3.0;
        return z_avg * a.cross(b) / 2.0;
    };
    rep(i, 0, n) {
        int j = (i + 1) % n;
        P a = pts[i], b = pts[j];
        res += vol(a, zs[i], b, zs[j]);
    }
    cout << setprecision(2) << fixed << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

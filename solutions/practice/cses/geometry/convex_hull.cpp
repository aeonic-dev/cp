#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

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

typedef Point<ll> P;

template<class P>
vector<P> convexHull(vector<P> poly) {
    int n = sz(poly);
    vector<P> hull(n + 1);
    sort(all(poly));
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && hull[k - 2].cross(hull[k - 1], poly[i]) < 0) k--;
        hull[k++] = poly[i];
    }
    for (int i = n - 1, t = k + 1; i > 0; i--) {
        while (k >= t && hull[k - 2].cross(hull[k - 1], poly[i - 1]) < 0) k--;
        hull[k++] = poly[i - 1];
    }
    hull.resize(k - 1);
    return hull;
}

void solve() {
    int n;
    cin >> n;
    vector<P> pts(n);
    for (auto &[x, y] : pts) cin >> x >> y;
    auto hull = convexHull(pts);
    
    cout << sz(hull) << "\n";
    for (auto [x, y] : hull) cout << x << " " << y << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

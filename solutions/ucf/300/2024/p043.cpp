#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
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
    Point(T x = 0, T y = 0) : x(x), y(y) {}
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
    ld angle() const { return atan2l(y, x); }
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
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

P normalized_dir(P a, P b) {
    P d = b - a;
    ll g = gcd(abs(d.x), abs(d.y));
    return {d.x / g, d.y / g};
}

void solve() {
    int n, m;
    cin >> n;

    vector<pair<P, P>> segs(n);
    set<P> pts;
    for (auto &[a, b] : segs) {
        cin >> a.x >> a.y >> b.x >> b.y;
        pts.insert(a);
        pts.insert(b);
    }

    ll res = 0;
    for (auto &[a, b] : segs) {
        map<P, map<P, ll>> left, rght;
        for (auto [c, d] : segs) {
            if (a == c || a == d
                || b == c || b == d) continue;

            bool onc = onSegment(a, b, c);
            bool ond = onSegment(a, b, d);
            if (!(onc ^ ond)) continue;
            if (ond) swap(c, d);

            int side = sideOf(a, b, d);
            if (side == 0) continue;

            P dir = normalized_dir(c, d);
            (side > 0 ? left : rght)[c][dir]++;
        }
        // cout << a << " -> " << b << '\n';

        for (auto &[p, dirs] : left) {
            ll sum_left = 0, sqr_left = 0;
            // cout << "left @ " << p << " {\n";
            for (auto [dir, num] : dirs) {
                sum_left += num;
                sqr_left += num * num;
                // cout << "  " << dir << ": " << num << '\n';
            }
            // cout << "}\n";
            res += sum_left * sum_left - sqr_left;
        }
        for (auto &[p, dirs] : rght) {
            ll sum_rght = 0, sqr_rght = 0;
            // cout << "rght @ " << p << " {\n";
            for (auto [dir, num] : dirs) {
                sum_rght += num;
                sqr_rght += num * num;
                // cout << "  " << dir << ": " << num << '\n';
            }
            // cout << "}\n";
            res += sum_rght * sum_rght - sqr_rght;
        }
    }
    cout << res / 2 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

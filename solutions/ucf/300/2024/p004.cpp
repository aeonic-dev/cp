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
    bool operator<(P p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    bool operator==(P p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const {
        return (a - *this).cross(b - *this);
    }
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
typedef Point<ld> Pd;

const ld eps = 1e-8l;
void solve() {
    int n;
    cin >> n;
    vector<P> pts(n);
    for (auto &[x, y] : pts) cin >> x >> y;
    cout << setprecision(8) << fixed;

    ll A2 = 0, A2l = 0;
    rep(i, 2, n) A2 += pts[0].cross(pts[i - 1], pts[i]);
    // cout << "A2 = " << A2 << "\n";
    int l = 1;
    for (; l < n - 1; l++) {
        ll A2ln = A2l + pts[0].cross(pts[l], pts[l + 1]);
        // cout << "A2ln = " << A2ln << "\n";
        // if (A2ln * 2 == A2)
        //     return void(cout << pts[l + 1].x << " "
        //                      << pts[l + 1].y << "\n");
        if (A2ln * 2 > A2) {
            l++;
            break;
        }
        A2l = A2ln;
    }
    l--;
    // cout << "l = " << l << "\n";

    ld tgt = A2 / 2.l - A2l;
    // cout << "tgt = " << tgt << "\n";
    Pd p{(ld) pts[0].x, (ld) pts[0].y},
            lo{(ld) pts[l].x, (ld) pts[l].y},
            hi{(ld) pts[l + 1].x, (ld) pts[l + 1].y},
            mp, a{lo.x, lo.y};
    rep(_, 0, 50) {
        mp = lo + (hi - lo) * .5l;

        ld A = p.cross(a, mp);
        // cout << "A = " << A << "\n";
        // cout << "A2tri = " << (A2l + A2tri) * 2 << "\n";

        if (abs(A - tgt) < eps) break;
        if (A > tgt) hi = mp;
        else lo = mp;
    }
    cout << mp.x << " " << mp.y << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

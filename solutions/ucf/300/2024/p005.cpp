#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

template<class T>
struct Q {
    T a, b;
    Q(T p, T q = 1) {
        T g = gcd(p, q);
        a = p / g;
        b = q / g;
        if (b < 0) a = -a, b = -b;
    }
    T gcd(T x, T y) const { return ::gcd(x, y); }
    
    bool operator==(const Q &o) const { return a * o.b == o.a * b; }
    bool operator<(const Q &o) const { return a * o.b < o.a * b; }
    bool operator>(const Q &o) const { return a * o.b > o.a * b; }
    Q operator+(const Q &o) const { return {a * o.b + o.a * b, b * o.b}; }
    Q operator-(const Q &o) const { return *this + Q(-o.a, o.b); }
    Q operator*(const Q &o) const { return {a * o.a, b * o.b}; }
    Q operator/(const Q &o) const { return *this * Q(o.b, o.a); }
    Q recip() const { return {b, a}; }
    int sgn() const { return (a > 0) - (a < 0); }
    friend ostream &operator<<(ostream &out, const Q &o) { return out << o.a << " " << o.b; }
    
    Q abs() const { return Q(::abs(a), ::abs(b)); }
    Q lowest() const { return Q(a, b); }
    Q perp() const { return Q(-b, a); }
    void reduce() { *this = lowest(); }
};

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
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

typedef Q<ll> F;
typedef Point<F> P;

F inf = 1e2;
P lineInter(const P &s1, const P &e1, const P &s2, const P &e2) {
    auto det = F(0) - (e1 - s1).cross(e2 - s2);
    if (det == 0) return P(inf, inf);
    auto t = (e2 - s2).cross(s2 - s1) / det;
    return s1 + (e1 - s1) * t;
}

void solve() {
    int n;
    P p{F(-1), F(0)};
    F m(1);
    cin >> m.a >> m.b >> n;
    
    rep(i, 0, n + 1) {
        P u = p, v = p + P(m.b, m.a);
        vector<P> pts{
                lineInter(u, v, P{-1, 1}, P{1, 1}),
                lineInter(u, v, P{-1, -1}, P{1, -1}),
                lineInter(u, v, P{-1, -1}, P{-1, 1}),
                lineInter(u, v, P{1, -1}, P{1, 1})
        };
        for (P np : pts) {
            if (p.x == np.x) continue;
            if (p.y.abs() == 1 && p.y == np.y) continue;
            if (np.x.abs() > 1 || np.y.abs() > 1) continue;
            p = np;
            break;
        }
        m = F(0) - m;
    }
    cout << p.x << " " << p.y << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

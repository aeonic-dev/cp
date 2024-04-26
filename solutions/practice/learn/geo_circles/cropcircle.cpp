#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef long double ld;

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
    
    ld dist() const { return sqrt((ld) dist2()); }
    
    ld dist(P p) const {
        return (p - *this).dist();
    }
    
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2(y, x); }
    
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

const ld eps = 1e-6;
typedef Point<ld> P;

ld ccRadius(const P &A, const P &B, const P &C) {
    return (B - A).dist() * (C - B).dist() * (A - C).dist() /
           abs((B - A).cross(C - A)) / 2;
}

P ccCenter(const P &A, const P &B, const P &C) {
    P b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}

bool eq(P lhsp, P rhsp) { return (rhsp - lhsp).dist2() < eps * eps; }
bool eq(ld lhs, ld rhs) { return abs(rhs - lhs) < eps; }
void solve() {
    int n, t = 0;
    while (t++, cin >> n, n) {
        vector<P> pts(n);
        rep(i, 0, n) cin >> pts[i].x;
        rep(i, 0, n) cin >> pts[i].y;
        
        set < vi > circles;
        rep(i, 0, n) {
            rep(j, i + 1, n) {
                rep(k, j + 1, n) {
                    P a = pts[i], b = pts[j], c = pts[k];
                    if (abs(a.cross(b, c)) < eps) continue;
                    
                    P cc = ccCenter(a, b, c);
                    ld r = ccRadius(a, b, c);
                    
                    set<int> s{i, j, k};
                    rep(l, 0, n) {
                        if (l == i || l == j || l == k) continue;
                        P d = pts[l];
                        P cc1 = ccCenter(a, b, d),
                                cc2 = ccCenter(b, c, d),
                                cc3 = ccCenter(c, a, d);
                        ld r1 = ccRadius(a, b, d),
                                r2 = ccRadius(b, c, d),
                                r3 = ccRadius(c, a, d);
                        if ((eq(cc, cc1) && eq(r, r1)
                             || (eq(cc, cc2) && eq(r, r2)
                                 || (eq(cc, cc2) && eq(r, r3)))))
                            s.insert(l);
                    }
                    circles.emplace(all(s));
                }
            }
        }
        
        cout << "Circles for boulder set #"
             << t << ": " << sz(circles) << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();
    
    return 0;
}

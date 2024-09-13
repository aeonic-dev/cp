#include <bits/stdc++.h>

#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
using namespace std;
#define vec vector
#define all(s) s.begin(), s.end()
#define rep(i, s, e) for(int i = s; i < e; i++)
typedef long long ll;
typedef long double ld;

template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    bool operator<(P p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    
    bool operator==(P p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
    
    P operator+(P p) const {
        return {x + p.x, y + p.y};
    }
    
    P operator-(P p) const {
        return {x - p.x, y - p.y};
    }
    
    P operator*(T d) const {
        return {x * d, y * d};
    }
    
    P operator/(T d) const {
        return {x / d, y / d};
    }
    
    T dot(P p) const {
        return x * p.x + y * p.y;
    }
    
    T cross(P p) const {
        return x * p.y - y * p.y;
    }
    
    T cross(P a, P b) const {
        return (a - *this).cross(b - *this);
    }
    
    T dist2() const {
        return x * x + y * y;
    }
    
    T dist() const {
        return sqrt((ld) dist2());
    }
    
    ld dist2(P p) const {
        return (p - *this).dist2();
    }
    
    T dist(P p) const {
        return sqrt((ld) dist2(p));
    }
    
    ld angle() const {
        return atan2(y, x);
    }
    
    P unit() const {
        return (*this) / dist();
    }
};

template<class P>
bool onSegment(P s, P e, P p, ld eps = 1e-6) {
    return (abs(p.cross(s, e)) < eps && (s - p).dot(e - p) <= 0 + eps);
}

template<class P>
vec<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
            oc = a.cross(b, c), od = a.cross(b, d);
    // checks if inter is single non-endpoint
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        return {(a * ob - b * oa) / (ob - oa)};
    }
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

typedef Point<ld> P;
map<ld, P> pos_dp[2];

const ld eps = 1e-6;

void solve() {
    int n;
    cin >> n;
    vec<P> pn(n);
    vec<ld> pxn(n, 0);
    rep(i, 0, n) {
        cin >> pn[i].x >> pn[i].y;
        if (i > 0) {
            pxn[i] = pxn[i - 1] + pn[i].dist(pn[i - 1]);
        }
    }
    ld tdn = pxn[n - 1]; // total distance on the n path
    
    int m;
    cin >> m;
    vec<P> pm(m);
    vec<ld> pxm(m, 0);
    rep(i, 0, m) {
        cin >> pm[i].x >> pm[i].y;
        if (i > 0) {
            pxm[i] = pxm[i - 1] + pm[i].dist(pm[i - 1]);
        }
    }
    ld tdm = pxm[m - 1]; // total distance on the m path
    
    auto lerp = [&](P &a, P &b, ld f) {
        return a + (b - a) * f;
    };
    
    auto find_min = [&](P a, P b, P c, P d) {
        ld l = 0, r = 1, d1, d2;
        rep(i, 0, 200) {
            ld m1 = l + (r - l) / 3;
            ld m2 = r - (r - l) / 3;
            d1 = lerp(a, b, m1).dist(lerp(c, d, m1));
            d2 = lerp(a, b, m2).dist(lerp(c, d, m2));
            if (d1 > d2) l = m1;
            else r = m2;
        }
        return d1;
    };
    
    
    int i = 0, j = 0;
    P cn = pn[0], cm = pm[0];
    ld min = LDBL_MAX;
    while (i < n - 1 && j < m - 1) {
        P on = cn, om = cm;
        ld difn = cn.dist(pn[i + 1]);
        ld difm = cm.dist(pm[j + 1]);
        
        if (difn < difm) {
            cn = pn[++i];
            cm = cm + (pm[j + 1] - cm).unit() * difn;
        } else {
            cm = pm[++j];
            cn = cn + (pn[i + 1] - cn).unit() * difm;
        }
        
        ld res = find_min(on, cn, om, cm);
        min = ::min(min, res);
    }
    
    cout << setprecision(12) << fixed;
    cout << min << endl;
}

int main() {
    solve();
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, s, e) for (int i = s; i < (e); i++)
typedef long long ll;
typedef long double ld;

const ld eps = 1e-8;
const int fac = 100;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    P operator+(P p) const { return {x + p.x, y + p.y}; }
    P operator-(P p) const { return {x - p.x, y - p.y}; }
    P operator*(T d) const { return {x * d, y * d}; }
    P operator/(T d) const { return {x / d, y / d}; }
    bool operator==(P p) const { return abs(x - p.x) <= eps && abs(y - p.y) <= eps; }
    
    T dot(P p) const { return x * p.x + y * p.y; }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld) dist2()); }
    P unit() const { return *this / dist(); }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P v, P w) const { return (v - *this).cross(w - *this); }
    P perp() const { return {-y, x}; }
    
    void round() {
        x = ::round(x), y = ::round(y);
    }
};

typedef Point<ld> P;

ld lineDist(P s, P e, P p) { return (e - s).cross(p - s) / (e - s).dist(); }
vector<pair<P, P>> extTangents(P u, P v) {
    P dir = v - u, per = dir.perp().unit() * fac;
    return {
            {u + per, v + per},
            {u - per, v - per}
    };
}

int main() {
    int n;
    cin >> n;
    vector<P> pts(n);
    rep(i, 0, n) {
        ld x, y;
        cin >> x >> y;
        pts[i] = {x * fac, y * fac};
        pts[i].round();
    }
    
    int res = 1;
    rep(i, 0, n) {
        int num = 1;
        rep(j, i + 1, n) {
            if (pts[i] == pts[j]) num++;
        }
        res = ::max(res, num);
    }
    
    rep(i, 0, n) {
        P u = pts[i];
        rep(j, 0, n) {
            P v = pts[j];
            if (i == j || u == v) continue;
            
            for (auto [s, e] : extTangents(u, v)) {
                int num = 0;
                for (P w : pts) {
                    if (abs(lineDist(s, e, w)) <= fac + eps) num++;
                }
                res = max(res, num);
            }
        }
    }
    cout << res << "\n";
    
    return 0;
}

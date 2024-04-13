#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

template<class T>
struct Point3D {
    typedef Point3D P;
    typedef const P &R;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(R p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z);
    }
    bool operator==(R p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z);
    }
    P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(R p) const {
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double) dist2()); }
    //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    double phi() const { return atan2(y, x); }
    //Zenith angle (latitude) to the z-axis in interval [0, pi]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    P unit() const { return *this / (T) dist(); } //makes dist()=1
    //returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    //returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
    }
};

typedef Point3D<double> P3;

struct PR {
    void ins(int x) { (a == -1 ? a : b) = x; }
    void rem(int x) { (a == x ? a : b) = -1; }
    int cnt() { return (a != -1) + (b != -1); }
    int a, b;
};

struct F { P3 q; int a, b, c; };

vector<F> hull3d(const vector<P3> &A) {
    assert(sz(A) >= 4);
    vector<vector<PR>> E(sz(A), vector<PR>(sz(A), {-1, -1}));
#define E(x, y) E[f.x][f.y]
    vector<F> FS;
    auto mf = [&](int i, int j, int k, int l) {
        P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
        if (q.dot(A[l]) > q.dot(A[i]))
            q = q * -1;
        F f{q, i, j, k};
        E(a, b).ins(k);
        E(a, c).ins(j);
        E(b, c).ins(i);
        FS.push_back(f);
    };
    rep(i, 0, 4) rep(j, i + 1, 4) rep(k, j + 1, 4)mf(i, j, k, 6 - i - j - k);
    
    rep(i, 4, sz(A)) {
        rep(j, 0, sz(FS)) {
            F f = FS[j];
            if (f.q.dot(A[i]) > f.q.dot(A[f.a])) {
                E(a, b).rem(f.c);
                E(a, c).rem(f.b);
                E(b, c).rem(f.a);
                swap(FS[j--], FS.back());
                FS.pop_back();
            }
        }
        int nw = sz(FS);
        rep(j, 0, nw) {
            F f = FS[j];
#define C(a, b, c) if (E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
            C(a, b, c);
            C(a, c, b);
            C(b, c, a);
        }
    }
    for (F &it : FS)
        if ((A[it.b] - A[it.a]).cross(
                A[it.c] - A[it.a]).dot(it.q) <= 0)
            swap(it.c, it.b);
    return FS;
};

double segDist(P3 s, P3 e, P3 p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}

void solve() {
    int n;
    cin >> n;
    vector<P3> pts(n);
    for (auto &[x, y, z] : pts) cin >> x >> y >> z;
    auto hull = hull3d(pts);
    
    // get min dist from p to the face
    auto mind = [&](F f, P3 p) -> double {
        vector<P3> tri{pts[f.a], pts[f.b], pts[f.c]};
        
        // check if we project to a point inside the face
        int csgn = 0, in = 1;
        rep(i, 0, 3) {
            P3 a = tri[i], b = tri[(i + 1) % 3];
            P3 N = (b - a).cross(f.q);
            
            double dot = (p - a).dot(N);
            int sgn = (dot > 0) - (dot < 0);
            
            if (!i) csgn = sgn;
            else if (sgn != csgn) in = 0;
        }
        
        // if so, min is distance to the plane
        if (in) {
            P3 v = tri[0] - p;
            return v.dot(f.q.unit());
        }
        
        // min segment distance
        double res = DBL_MAX;
        rep(i, 0, 3) {
            P3 s = tri[i], e = tri[(i + 1) % 3];
            res = min(res, segDist(s, e, p));
        }
        return res;
    };
    
    int q;
    cin >> q;
    cout << setprecision(4) << fixed;
    rep(i, 0, q) {
        P3 w;
        cin >> w.x >> w.y >> w.z;
        
        double res = DBL_MAX;
        for (F f : hull)
            res = min(res, mind(f, w));
        cout << res << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

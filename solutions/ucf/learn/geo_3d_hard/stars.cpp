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

typedef Point3D<double> P;
const double pi = acos(-1);

struct PR {
    void ins(int x) { (a == -1 ? a : b) = x; }
    void rem(int x) { (a == x ? a : b) = -1; }
    int cnt() { return (a != -1) + (b != -1); }
    int a, b;
};

struct F { P q; int a, b, c; };

vector<F> hull3d(const vector<P> &A) {
    assert(sz(A) >= 4);
    vector<vector<PR>> E(sz(A), vector<PR>(sz(A), {-1, -1}));
#define E(x, y) E[f.x][f.y]
    vector<F> FS;
    auto mf = [&](int i, int j, int k, int l) {
        P q = (A[j] - A[i]).cross((A[k] - A[i]));
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

double ccRadius(const P &A, const P &B, const P &C, const P &N) {
    return (B - A).dist() * (C - B).dist() * (A - C).dist() /
           abs((B - A).cross(C - A).dot(N)) / 2;
}
P ccCenter(const P &A, const P &B, const P &C, const P &N) {
    P b = C - A, c = B - A;
    return A - (b * c.dist2() - c * b.dist2()).cross(N) // dot with downward normal flips the sign
               / b.cross(c).dot(N) / 2;
}

pair<P, double> mec(vector<P> ps, P N) { // downward normal
    shuffle(all(ps), mt19937(time(0)));
    P o = ps[0];
    double r = 0, EPS = 1 + 1e-8;
    rep(i, 0, sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
            o = ps[i], r = 0;
            rep(j, 0, i) if ((o - ps[j]).dist() > r * EPS) {
                    o = (ps[i] + ps[j]) / 2;
                    r = (o - ps[i]).dist();
                    rep(k, 0, j) if ((o - ps[k]).dist() > r * EPS) {
                            o = ccCenter(ps[i], ps[j], ps[k], N);
                            r = (o - ps[i]).dist();
                        }
                }
        }
    return {o, r};
}

// {projection, plane distance}
pair<P, double> proj(const vector<P> &pts, F f, P p) {
    P a = pts[f.a], N = f.q.unit();
    double d = (a - p).dot(N);
    
    return {p + N * d, d};
}

void solve() {
    int n;
    cin >> n;
    
    vector<P> pts(n);
    for (auto &[x, y, z] : pts) cin >> x >> y >> z;
    auto hull = hull3d(pts);
    
    double res = DBL_MAX;
    for (F f : hull) {
        double h = 0; // cylinder height
        vector<P> pln;
        for (P o : pts) {
            auto [p, d] = proj(pts, f, o);
            pln.push_back(p), h = max(h, d);
        }
        
        auto [c, r] = mec(pln, f.q);
        double vol = pi * r * r * h;
        res = min(res, vol);
    }
    cout << setprecision(7) << fixed << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

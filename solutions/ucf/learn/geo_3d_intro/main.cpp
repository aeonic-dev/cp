#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

/*
 * Usage: 
 */
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

    friend ostream &operator<<(ostream &o, const P &p) {
        return o << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    }
};

typedef Point3D<ld> P;
const ld eps = 1e-8;

template<class T>
struct Line {
    P o, d; // (x,y,z) = o + td
    Line(P a, P b) : d(b - a), o(a) {}
};

template<class T>
struct Plane {
    P N; T d;
    Plane(P N, P p) : N(N), d(N.dot(p)) {}
    Plane(P p, P q, P r) : Plane((q - p).cross(r - p), p) {}

    int side(P p) {
        // signed distance?
        return N.dot(p) - d;
    }

    P inter(Line<T> ln) {
        // gets intersection point, assuming there's exactly 1
        return ln.o - ln.d * side(ln.o) / N.dot(ln.d);
    }
};

typedef Plane<ld> Pl;
typedef Line<ld> Ln;

int sgn(int v) { return (v > -eps) - (v < eps); }

void solve() {
    P p, q, r, u, v;
    while (cin >> p.x >> p.y >> p.z
           >> q.x >> q.y >> q.z
           >> r.x >> r.y >> r.z
           >> u.x >> u.y >> u.z
           >> v.x >> v.y >> v.z) {
        Pl pl(p, q, r);
        Ln ln(u, v);

        // cout << "pl.N = " << pl.N << "\n";
        // cout << "p,q,r" << p << " " << q << " " << r << "\n";

        int su = pl.side(u), sv = pl.side(v);
        if (abs(su - sv) < eps) {
            cout << "Yes\n";
            continue;
        }

        P w = pl.inter(ln);
        // cout << "Inter is " << w << "\n";
        Pl a(p, q, p + pl.N), b(q, r, q + pl.N), c(r, p, r + pl.N);
        set<int> sides{sgn(a.side(w)), sgn(b.side(w)), sgn(c.side(w))};
        // for (int x: sides) cout << x << " ";
        // cout << "from " << sgn(a.side(w)) << " " <<  sgn(b.side(w)) << " " << sgn(c.side(w)) << "\n";
        // cout << "Ns " << a.N << " " << b.N << " " << c.N << "\n\n";
        // cout << "c is " << r << " " << p << " " << r + pl.N << "\n";
        // cout << "\n";

        if (sz(sides) == 1) cout << "No\n";
        else cout << "Yes\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

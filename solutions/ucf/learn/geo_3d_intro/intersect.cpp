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

int sgn(int v) { return (v > 0) - (v < 0); }

int tc = 0;
void solve() {
    P A, B, C, P, Q;
    cin >> P.x >> P.y >> P.z
            >> Q.x >> Q.y >> Q.z
            >> A.x >> A.y >> A.z
            >> B.x >> B.y >> B.z
            >> C.x >> C.y >> C.z;

    Plane<ld> p(A, B, C);
    Line<ld> ln(P, Q);
    int sp = p.side(P), sq = p.side(Q);

    cout << "Data Set #" << ++tc << ":\n"
         << setprecision(1) << fixed;
    if (abs(sp) < eps && abs(sq) < eps) cout << "The line lies on the plane.\n";
    else if (abs(sp - sq) < eps) cout << "There is no intersection.\n";
    else cout << "The intersection is the point " << p.inter(ln) << ".\n";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

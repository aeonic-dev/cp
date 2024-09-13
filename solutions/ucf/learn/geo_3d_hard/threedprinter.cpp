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

typedef long double ld;
typedef Point3D<ld> P;

void solve() {
    int n;
    cin >> n;
    
    ld res = 0;
    rep(_, 0, n) {
        int f;
        cin >> f;
        
        vector<vector<P>> faces(f);
        int num = 0;
        P com = P();
        
        rep(i, 0, f) {
            int v;
            cin >> v;
            
            auto &vec = faces[i] = vector<P>(v);
            for (auto &[x, y, z] : vec) {
                cin >> x >> y >> z;
                com = com + P{x, y, z}, num++;
            }
        }
        
        com = com / num;
        for (const auto &pol : faces) {
            P a = pol[0];
            P N = (pol[1] - a).cross(pol[2] - a);
            ld dot = N.dot(a - com);
            int sgn = (dot > 0) - (dot < 0);
            
            rep(k, 1, sz(pol) - 1) {
                P b = pol[k], c = pol[k + 1];
                res += sgn * a.cross(b).dot(c) / 6.0;
            }
        }
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

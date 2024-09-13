#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const ld pi = acos(-1);

template<class T>
struct Point3D {
    typedef Point3D P;
    typedef const P &R;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    static P polar(ld r, ld lat, ld lon) {
        ld theta = lat * pi / 180;
        ld phi = lon * pi / 180;
        return P{
                cos(theta) * cos(phi),
                cos(theta) * sin(phi),
                sin(theta)
        } * r;
    }
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

typedef Point3D<ld> P;
const ld r = 6371;

void solve() {
    P a, b, p(0, 0, r);
    ld lat, lon;
    cin >> lat >> lon, a = P::polar(r, lat, lon);
    cin >> lat >> lon, b = P::polar(r, lat, lon);
    
    P N = a.cross(b);
    P proj = p - N * p.dot(N) / N.dist2();
    P apog = proj.unit() * r;
    
    ld d_apog = (apog - p).dist();
    ld d_endp = min((a - p).dist(), (b - p).dist());
    
    if (a.cross(apog).dot(N) > 0
        && b.cross(apog).dot(N) < 0
        && d_apog < d_endp) {
        cout << "Alex\n" << d_apog;
    } else cout << "Timothy\n" << d_endp;
    cout << "\n\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(6) << fixed;
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;


template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }

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
const ld eps = 0.1;

template<class T>
struct Line {
    P o, d; // (x,y,z) = o + td
    Line(P a, P b) : d(b - a), o(a) {}
};

template<class T>
struct Plane {
    P N;
    T d;
    Plane(P N, P p) : N(N), d(N.dot(p)) {}
    Plane(P p, P q, P r) : Plane((q - p).cross(r - p), p) {}
    Plane(T a, T b, T c, T d) : N(a, b, c), d(d) {}

    int side(P p) {
        // signed distance?
        return N.dot(p) - d;
    }

    bool on(P p) {
        return abs(side(p)) < eps;
    }

    pair<bool, Line<T>> pinter(Plane o) {
        // parallel => no intersection
        P c = N.cross(o.N);
        if (c.dist() < eps) return {false, {P(), P()}};

        // otherwise we have a line
        P O = (o.N * d - N * o.d).cross(c) / c.dist2();
        return {true, Line<T>(O, O + c)};
    }

    P inter(Line<T> ln) {
        // gets intersection point, assuming there's exactly 1
        return ln.o - ln.d * side(ln.o) / N.dot(ln.d);
    }

    bool operator|(Plane pl) { // parallel?
        return N.cross(pl.N).dist() < eps;
    }
};

typedef Point3D<double> P3;

struct PR {
    void ins(int x) { (a == -1 ? a : b) = x; }
    void rem(int x) { (a == x ? a : b) = -1; }
    int cnt() { return (a != -1) + (b != -1); }
    int a, b;
};

struct F {
    P3 q;
    int a, b, c;
};

typedef Plane<ld> Pl;
typedef Line<ld> Ln;

typedef ld d;
#define S(a, b) (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6

template<class F>
d rec(F &f, d a, d b, d eps, d S) {
    d c = (a + b) / 2;
    d S1 = S(a, c), S2 = S(c, b), T = S1 + S2;
    if (abs(T - S) <= 15 * eps || b - a < 1e-10)
        return T + (T - S) / 15;
    return rec(f, a, c, eps / 2, S1) + rec(f, c, b, eps / 2, S2);
}
template<class F>
d quad(d a, d b, F f, d eps = 1e-8) {
    return rec(f, a, b, eps, S(a, b));
}

void solve() {
    int tc;
    ld L, W, H, A, B, C, D;
    cin >> tc >> L >> W >> H >> A >> B >> C >> D;
    Pl pl(A, B, C, D);

    // top face points, counterclockwise
    P a_u(0, 0, H), b_u(L, 0, H), c_u(L, W, H), d_u(0, W, H);
    P a_d(0, 0, 0), b_d(L, 0, 0), c_d(L, W, 0), d_d(0, W, 0);

    Pl up(a_u, b_u, c_u), down(a_d, b_d, c_d),
            front(a_u, b_u, a_d), back(c_u, d_u, c_d),
            left(a_u, d_u, a_d), right(b_u, c_u, b_d);
    vector<Pl> pls{up, down, front, right, back, left};

    vector<P> inters, top, main;
    for (P p : vector{a_u, b_u, c_u, d_u, a_d, b_d, c_d, d_d}) {
        if (pl.side(p) < eps) inters.push_back(p);
    }

    for (Pl pl1 : pls) {
        if (pl | pl1) continue;
        for (Pl pl2 : pls) {
            if ((pl | pl2) || (pl1 | pl2)) continue;
            if (!pl1.pinter(pl2).first
                || !pl1.pinter(pl).first
                || !pl.pinter(pl2).first) continue;

            auto [f, ln] = pl.pinter(pl2);
            if (!f) continue;

            if (abs(pl1.N.dot(ln.d)) < eps) continue;
            // cout << "ln " << ln.d << " " << ln.o << "\n";

            P p = pl1.inter(ln);

            // cout << "inter " << p << "\n";

            if (p.x < -eps || p.x > L + eps
                || p.y < -eps || p.y > W + eps
                || p.z < -eps || p.z > H + eps)
                continue;

            inters.push_back(p);
        }
    }
    for (P p : inters) {
        // cout << p << "\n";
        if (up.on(p)) top.push_back(p);
        if (pl.on(p)) main.push_back(p);
    }

    ld res = 0;
    for (auto &ovec : vector{top, main}) {
        if (ovec.empty()) continue;

        // this is so fucked lol
        sort(all(ovec));
        vector<P> vec;
        rep(i, 0, sz(ovec)) {
            P p = ovec[i];
            rep(j, 0, sz(vec)) {
                if ((vec[j] - p).dist() < eps) goto next;
            }
            vec.push_back(p);
        next:;
        }
        P piv = vec[0];
        sort(1 + all(vec), [&](P a, P b) -> bool {
            ld pa = (a-piv).phi(), pb = (b-piv).phi();
            ld ta = (a-piv).theta(), tb = (b-piv).theta();

            if (abs(pa - pb) < eps) return abs(ta - tb) > eps && ta < tb;
            return pa < pb;
        });

        // for (P p : vec) cout << "\t" << p << "\n";
        // cout << "\n";

        if (sz(vec) < 3) continue;

        rep(i, 1, sz(vec) - 1) {
            P a = piv, b = vec[i], c = vec[i + 1];
            ld ab = (b - a).dist(), bc = (c - b).dist(), ca = (a - c).dist();
            ld sp = (ab + bc + ca) / 2;

            res += sqrt(sp * (sp - ab) * (sp - bc) * (sp - ca));
        }
        // rep(i, 0, sz(vec) - 2) {
        //     P a = vec[i], b = vec[i + 1], c = vec[i + 2];
        //     ld ab = (b - a).dist(), bc = (c - b).dist(), ca = (a - c).dist();
        //     ld sp = (ab + bc + ca) / 2;

        //     res += sqrt(sp * (sp - ab) * (sp - bc) * (sp - ca));
        // }
    }
    cout << tc << " " << int(ceil(res)) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

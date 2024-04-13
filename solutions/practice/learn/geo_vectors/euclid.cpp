#include <bits/stdc++.h>

using namespace std;

#define vec vector
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

    double dist() const { return sqrt((double) dist2()); }

    double dist(P p) const {
        return (p - *this).dist();
    }

    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }

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

typedef Point<ld> P;

pair<P, P> get_h_g(P A, P B, P C, ld v) {
    P H = A + (C - A) * v;
    return {H, B + (H - A)};
}

ld round3(ld n) {
    return round(n * 1000) / 1000;
}

void solve() {
    while (true) {
        P A, B, C, D, E, F;
        cin >>
            A.x >> A.y >>
            B.x >> B.y >>
            C.x >> C.y >>
            D.x >> D.y >>
            E.x >> E.y >>
            F.x >> F.y;

        if (!(A.x != 0 || A.y != 0 ||
              B.x != 0 || B.y != 0 ||
              C.x != 0 || C.y != 0 ||
              D.x != 0 || D.y != 0 ||
              E.x != 0 || E.y != 0 ||
              F.x != 0 || F.y != 0))
            break;

        // area of triangle DEF
        ld tri = abs((E - D).cross(F - D)) / 2; // no abs?

        // find sin(angle CAB)
        P CA = C - A, BA = B - A;
        ld sinth = sqrt(1 - pow(CA.dot(BA) / (CA.dist() * BA.dist()), 2));

        // H at v=0-1 along A -> C
        ld v = tri / (A.dist(C) * A.dist(B) * sinth);
        auto res = get_h_g(A, B, C, v);
        auto H = res.first, G = res.second;

        cout << setprecision(3) << fixed;
        cout << round3(G.x) << " " << round3(G.y) << " " << round3(H.x) << " " << round3(H.y) << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    solve();

    return 0;
}

// Settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// Few word type fast zoom
#define vec vector
#define pb push_back
#define eb emplace_back
#define uset unordered_set
#define umap unordered_map

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<li, li> pli;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// Other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define gin(type) get_cin<type>()

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
// @formatter:on

// Templated point/vector impl for any numeric type.
template<typename n_t>
struct pt {
    n_t x, y;

    pt() : pt(0, 0) {}

    pt(n_t x, n_t y) : x(x), y(y) {
        static_assert(std::is_arithmetic<n_t>::value, "value type must be numeric");
    }

    static pt polar(n_t theta, n_t r) {
        return {r * cos(theta), r * sin(theta)};
    }

    friend std::istream &operator>>(std::istream &in, pt<n_t> &rhs) {
        in >> rhs.x >> rhs.y;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const pt<n_t> &rhs) {
        out << rhs.x << " " << rhs.y;
        return out;
    }

    pt operator+(const pt &r) const {
        return {x + r.x, y + r.y};
    }

    pt operator-(const pt &r) const {
        return {x - r.x, y - r.y};
    }

    pt operator*(n_t r) const {
        return {x * r, y * r};
    }

    pt operator/(n_t r) const {
        return {x / r, y / r};
    }

    bool operator==(const pt &u) const {
        return x == u.x && y == u.y;
    }

    bool operator<(const pt &u) const {
        if (x != u.x) return x < u.x;
        return y < u.y;
    }

    n_t distance(pt u) const {
        return sqrt(std::pow(x - u.x, 2) + std::pow(y - u.y, 2));
    }

    n_t distance2(pt u) const {
        return std::pow(x - u.x, 2) + std::pow(y - u.y, 2);
    }

    n_t dot(pt u) const {
        return x * u.x + y * u.y;
    }

    n_t cross(pt u) const {
        return x * u.y - y * u.x;
    }

    // Computes the cross product of (u - this vector) and (v - this vector), such as for area
    n_t cross(pt u, pt v) const {
        return (u - *this).cross(v - *this);
    }

    n_t norm() const {
        return x * x + y * y;
    }

    n_t mag() const {
        return std::sqrt(norm());
    }

    n_t theta() const {
        return atan2(y, x);
    }

    n_t angle(pt u) {
        return (u - *this).theta();
    }

    pt unit() const {
        n_t m = mag();
        return {x / m, y / m};
    }

    pt midpoint(pt u) const {
        return *this + (u - *this) / 2.0f;
    }

    // Projects the vector u onto this vector
    pt project(pt u) const {
        return unit() * dot(u) / mag();
    }

    // Gets the unit vectors perpendicular to this vector
    std::pair<pt, pt> perp() const {
        n_t m = mag();
        return {{y / m,  -x / m},
                {-y / m, x / m}};
    }
};

template<typename n_t>
struct seg {
    pt<n_t> a, b;

    seg(const pt<n_t> &a, const pt<n_t> &b) : a(a), b(b) {}

    static seg from(const pt<n_t> &start, const pt<n_t> &dir) {
        return seg(start, start + dir);
    }

    pt<n_t> dir() const {
        return b - a;
    }

    n_t distance(pt<n_t> v) const {
        auto u = dir();
        return std::abs(u.cross(v) / u.mag());
    }


    // Returns true if the segments intersect, and sets out to the intersection point
    // https://stackoverflow.com/a/565282
    bool intersection(const seg &o, pt<n_t> &out) const {
        const pt<n_t> &p = a, &q = o.a;
        pt<n_t> r = dir(), s = o.dir();

        // If the segments intersect, there exist some t,u such that p + tr = q + us
        n_t t = (q - p).cross(s) / r.cross(s);
        n_t u = (q - p).cross(r) / r.cross(s);

        if (r.cross(s) == 0) {
            if ((q - p).cross(r) == 0) {
                // Collinear
                n_t t0 = (q - p).cross(r) / r.norm();
                n_t t1 = t0 + s.dot(r) / r.norm();
                if (t0 > t1) swap(t0, t1);

                // TODO: Pick more consistent intersection points in collinear cases
                if (t0 >= 0 && t1 <= 0) {
                    // Collinear, intersecting at [t0, t1]
                    out = p + r * t0;
                    return true;
                }
                if (t0 <= 0 && t1 >= 0) {
                    // Collinear, intersecting at [0, min(1, t1)]
                    out = p + r * min((n_t) 1, t1);
                    return true;
                }
                if (t0 <= 1 && t1 >= 1) {
                    // Collinear, intersecting at [max(0, t0), 1]
                    out = p + r * max((n_t) 0, t0);
                    return true;
                }

                // Collinear, not intersecting
                return false;
            }
            // Parallel, not intersecting
            return false;
        }

        if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
            // Not parallel, intersecting
            out = p + r * t;
            return true;
        }

        // Not parallel, not intersecting
        return false;
    }
};

// Returns the absolute area of the triangle formed by the points a, b and c
template<typename n_t>
n_t area(const pt<n_t> &a, const pt<n_t> &b, const pt<n_t> &c) {
    pt<n_t> u = b - a, v = c - a;
    return std::abs(u.cross(v)) / (n_t) 2;
}

typedef pt<ld> dpt;
typedef seg<ld> dsg;

const double eps = 1e-6;
int tc = 0;

void solve() {
    int n;
    cin >> n;

    vec<dpt> pts(n);
    cin >> pts;

    // {{p1, p2, p3, p4} indices sorted ascending
    set<vec<int>> ts;
    rep(i, 0, n) {
        dpt &p1 = pts[i];

        rep(j, 0, n) {
            if (i == j) continue;
            dpt &p2 = pts[j];

            rep(k, 0, n) {
                if (i == k || j == k) continue;
                dpt &p3 = pts[k];

                if (abs(p2.distance2(p1) - p2.distance2(p3)) < eps &&
                    abs(p1.angle(p2) - p1.angle(p3)) < eps) {

                    rep(l, 0, n) {
                        if (i == l || j == l || k == l) continue;
                        dpt &p4 = pts[l];

                        if ((abs(p2.angle(p3) - p2.angle(p4) + M_PI_2) < eps ||
                             abs(p2.angle(p3) - p2.angle(p4) - M_PI_2) < eps) &&
                            abs(p1.distance2(p3) - p2.distance2(p4)) < eps) {
                            vi t = {i, j, k, l};
                            sort(all(t));

                            ts.insert(t);
                        }
                    }
                }
            }
        }
    }

    cout << "Set #" << ++tc << ": " << ts.size() << "\n\n";
}

#define MULTIPLE_CASES 1

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)
#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}
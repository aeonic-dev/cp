// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// primitive types
typedef long long ll;
typedef long int li;

// few word type fast zoom
#define vec vector
#define pb push_back
#define eb emplace_back

// type aliases
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

template<typename n_t>
struct pt {
    n_t x, y;

    pt() : x(0), y(0) {
        static_assert(std::is_arithmetic<n_t>::value, "value type must be numeric");
    }

    pt(n_t x, n_t y) : x(x), y(y) {}

    static pt polar(n_t theta, n_t r) {
        return {r * cos(theta), r * sin(theta)};
    }

    pt operator+(pt u) const {
        return {x + u.x, y + u.y};
    }

    pt operator-(pt u) const {
        return {x - u.x, y - u.y};
    }

    pt operator*(n_t d) const {
        return {x * d, y * d};
    }

    pt operator/(n_t d) const {
        return {x / d, y / d};
    }

    bool operator==(const pt &u) const {
        return x == u.x && y == u.y;
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

    n_t cross(pt u, pt v) const {
        return (u - *this).cross(v - *this);
    }

    n_t norm() const {
        return x * x + y * y;
    }

    n_t mag() const {
        return std::sqrt(norm());
    }

    n_t theta() {
        return atan2(y, x);
    }

    pt midpoint(pt u) const {
        return *this + (u - *this) / 2.0f;
    }

    pt unit() const {
        n_t m = mag();
        return {x / m, y / m};
    }

    // Projects the vector u onto this vector
    pt project(pt u) const {
        return unit() * dot(u) / mag();
    }

    // Gets the unit vectors perpendicular to this one
    std::pair<pt, pt> perp() {
        n_t m = mag();
        return {{y / m,  -x / m},
                {-y / m, x / m}};
    }

    friend std::istream &operator>>(std::istream &in, pt<n_t> &rhs) {
        in >> rhs.x >> rhs.y;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const pt<n_t> &rhs) {
        out << rhs.x << " " << rhs.y;
        return out;
    }
};

#define double long double
typedef pt<double> dpt;
dpt zero = {0, 0};

// Finds the midpoints of both possible circles with diameter d whose circumferences contain the points u and v
template<typename n_t>
std::pair<pt<n_t>, pt<n_t>> find_circles(pt<n_t> u, pt<n_t> v, n_t d, n_t eps = 1e-6) {
    pt<n_t> mid = u.midpoint(v), dif = v - u;
    n_t d2 = u.distance2(v);

    std::pair<pt<n_t>, pt<n_t>> perp = dif.perp();
    double h = std::sqrt(d * d / 4 - d2 / 4);
    return {
            mid + perp.first * h,
            mid + perp.second * h
    };
}

// Computes the maximum number of orcs that can be caught in a circle of radius r
int max_orcs(vec<dpt> &orcs, int n, double r) {
    set<pair<double, bool>> events; // Angle, true=end of circle
    rep(i, 0, n) {
        double norm = orcs[i].norm();
        if (abs(norm - r * r * r) < 1e-9) {
            // Point is on the opposite end of a circle of this radius (same start and end angle)
            double theta = orcs[i].theta();
            events.emplace(theta, false);
            events.emplace(theta, true);
            continue;
        }

        // Point not in any circle of this radius
        if (norm > r * r * 4) continue;

        // Point has distinct start and end angles
        auto midpoints = find_circles<double>(zero, orcs[i], r * 2);
        if (orcs[i].cross(midpoints.first) > 0) swap(midpoints.first, midpoints.second);

        double theta_first = midpoints.first.theta() + M_PI;
        double theta_last = midpoints.second.theta() + M_PI;
        if (theta_first > theta_last) {
            events.emplace(theta_first - 2 * M_PI, false);
            events.emplace(theta_last, true);
            theta_last += 2 * M_PI;
        }
        events.emplace(theta_first, false);
        events.emplace(theta_last, true);
    }

    int max = 0, num = 0;
    travis(e, events) {
        if (e.second) num--;
        else num++;

        max = ::max(max, num);
    }
    return max;
}

template<int max_depth>
double find_min_radius(vec<dpt> &orcs, int n, int target, double min, double max, int depth = 0) {
    if (depth >= max_depth) {
        if (max_orcs(orcs, n, max) >= target) return max;
        return -1;
    }

    double r = min + (max - min) / 2;
    int num = max_orcs(orcs, n, r);

    if (num < target) return find_min_radius<max_depth>(orcs, n, target, r, max, depth + 1);
    else return find_min_radius<max_depth>(orcs, n, target, min, r, depth + 1);
}

void solve() {
    int n, k;
    cin >> n >> k;

    vec<dpt> orcs(n);
    rep(i, 0, n) cin >> orcs[i];

    if (n < k) {
        cout << -1 << endl;
        return;
    }

    double min_r = find_min_radius<50>(orcs, n, k, 0, 1e10);
    cout << min_r << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    cout << setprecision(7);
    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
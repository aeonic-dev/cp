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

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
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
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
// @formatter:on=

template<typename n_t>
struct pt {
    n_t x, y;

    pt() : x(0), y(0) {
        static_assert(std::is_arithmetic<n_t>::value, "value type must be numeric");
    }

    pt(n_t x, n_t y) : x(x), y(y) {}

    friend std::istream &operator>>(std::istream &in, pt<n_t> &rhs) {
        in >> rhs.x >> rhs.y;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const pt<n_t> &rhs) {
        out << rhs.x << " " << rhs.y;
        return out;
    }

    pt operator+(const pt &u) const {
        return {x + u.x, y + u.y};
    }

    pt operator-(const pt &u) const {
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
};

// Constructs a convex hull with the given points, returning them in counterclockwise order.
template<typename n_t>
std::vector<pt<n_t>> convex(std::vector<pt<n_t>> pts, double eps = 1e-9) {
    if (pts.size() <= 1) return pts;

    std::sort(pts.begin(), pts.end());
    std::vector<pt<n_t>> hull(pts.size() + 1);

    int s = 0, hull_size = 0;
    for (int i = 2; i--; s = --hull_size, std::reverse(pts.begin(), pts.end())) {
        for (auto &p: pts) {
            while (hull_size >= s + 2 && hull[hull_size - 2].cross(hull[hull_size - 1], p) <= 0 + eps) hull_size--;
            hull[hull_size++] = p;
        }
    }

    return {
            hull.begin(),
            hull.begin() + hull_size - (hull_size == 2 && hull[0] == hull[1])
    };
}

// Finds all antipodal pairs for the given hull with rotating calipers, assuming points in counterclockwise order.
// Returns the biggest distance between any antipodal pair, or 0 if there are less than two points.
template<typename n_t>
n_t max_distance(const std::vector<pt<n_t>> &hull) {
    if (hull.size() <= 1) return (n_t) 0;
    if (hull.size() == 2) return hull[0].distance(hull[1]);

    int n = hull.size();
    int j = n >= 2;
    n_t max_d2 = 0;

    rep(i, 0, j) {
        for (;; j = (j + 1) % n) {
            max_d2 = max(max_d2, hull[i].distance2(hull[j]));
            if ((hull[(j + 1) % n] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0) break;
        }
    }

    return std::sqrt(max_d2);
}

typedef pt<double> dpt;

void solve() {
    int c;
    cin >> c;

    vec<dpt> pts(c), hull;
    cin >> pts;

    if (c == 2) {
        cout << pts[0].distance(pts[1]) << endl;
        return;
    }

    hull = convex(pts);
    auto max = max_distance(hull);
    cout << max << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // Unties cin from cout

    cout << setprecision(7) << fixed;
    solve();
}
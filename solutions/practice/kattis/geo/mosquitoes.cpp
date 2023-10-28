// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// primitive types
typedef long long ll;
typedef long int li;

// aliases
#define vec vector
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// more aliases
#define pb push_back
#define eb emplace_back

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

typedef pt<double> dpt;

vec<dpt> get_center_points(dpt u, dpt v, double d) {
    dpt mid = u.midpoint(v), dif = v - u;
    double dist = u.distance(v);

    if (abs(dist - d) <= 1e-6) {
        return vec<dpt>(1, mid);
    }

    pair<dpt, dpt> perp = dif.perp();
    double h = sqrt(d * d / 4.0f - dist * dist / 4.0f);
    return {
            mid + perp.first * h,
            mid + perp.second * h
    };
}

void solve() {
    int m;
    double d;
    cin >> m >> d;

    vec<dpt> bugs(m);
    rep(i, 0, m) cin >> bugs[i];

    int max = 1;
    rep(i, 0, m) {
        dpt u = bugs[i];

        rep(j, i + 1, m) {
            dpt v = bugs[j];
            if (u.distance(v) > d + 1e-6) continue;

            vec<dpt> centers = get_center_points(u, v, d);
            travis(c, centers) {
                int num = 0;
                rep(k, 0, m) {
                    if (c.distance(bugs[k]) <= d / 2.0f + 1e-5) num++;
                }
                max = ::max(max, num);
            }
        }
    }

    cout << max << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}
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
    std::pair <pt, pt> perp() const {
        n_t m = mag();
        return {{y / m,  -x / m},
                {-y / m, x / m}};
    }
};

struct dsu {
    vector<int> par;

    dsu(int n): par(n, -1) {}

    int find(int s) {
        return par[s] < 0 ? s : par[s] = find(par[s]);
    }

    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (par[a] > par[b]) swap(a, b); // a is larger
        par[a] += par[b];
        par[b] = a;

        return true;
    }
};

typedef pt<double> dpt;

void solve() {
    int n;
    while (cin >> n, n != 0) {
        vec<dpt> pts(n);
        cin >> pts;

        vec<tuple<double, int, int>> edges;
        edges.reserve(n * n);
        rep(i, 0, n) {
            rep(j, 0, n) {
                if (i == j) continue;
                edges.emplace_back(pts[i].distance(pts[j]), i, j);
            }
        }
        sort(all(edges));

        dsu s(n);
        ld sum = 0;
        travis(e, edges) {
            if (s.join(get<1>(e), get<2>(e))) sum += get<0>(e);
        }

        cout << setprecision(2) << fixed << round(sum * 100) / 100 << endl;
    }
}

#define MULTIPLE_CASES 0
int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}
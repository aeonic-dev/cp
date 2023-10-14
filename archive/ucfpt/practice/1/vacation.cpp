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
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type
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

typedef pt<ld> dpt;

ld cost(vec<vec<ld>> &dp, vec<vec<ld>> &edges, int n, int mask, int last) {
    if (mask == 0) return 0;

    if (dp[mask][last] == -1) {
        ld cost = LDBL_MAX;
        rep(i, 0, n) {
            if ((mask & (1 << i)) == 0) continue;
            cost = min(cost,
                       edges[last][i] +
                       ::cost(dp, edges, n, mask ^ (1 << i), i));
        }

        dp[mask][last] = cost;
    }

    return dp[mask][last];
}

int test = 0;
void solve() {
    int r, b;
    cin >> r >> b;

    vec<dpt> pts(r + 1);
    rep(i, 0, r) cin >> pts[i + 1];

    vec<vec<bool>> blocked(r + 1, vec<bool>(r + 1));
    rep(i, 0, b) {
        int p, q;
        cin >> p >> q;

        blocked[p][q] = true;
        blocked[q][p] = true;
    }

    vec<vec<ld>> edges(r + 1, vec<ld>(r + 1, LDBL_MAX));
    rep(i, 0, r + 1) {
        rep(j, 0, r + 1) {
            if (blocked[i][j]) continue;

            if (i == j) {
                edges[i][j] = 0;
                continue;
            }

            auto d = pts[i].distance(pts[j]);
            edges[i][j] = edges[j][i] = d + 120;
        }
    }

    vec<vec<ld>> dp(1 << (r + 1), vec<ld>(r + 1, -1));
    auto min_cost = cost(dp, edges, r + 1, (1 << (r + 1)) - 2, 0);

    cout << "Vacation #" << ++test << ":\n";
    if (min_cost == LDBL_MAX) cout << "Jimmy should plan this vacation a different day.\n\n";
    else {
        cout << "Jimmy can finish all of the rides in "
             << setprecision(3) << fixed
             << round(min_cost * 1000) / 1000
             << " seconds.\n\n";
    }
}

#define MULTIPLE_CASES 1

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
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

template<typename n_t>
n_t gcd(n_t a, n_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

template<typename n_t>
n_t lcm(n_t a, n_t b) {
    if (a == 0 || b == 0) return 0;
    return a * b / gcd(a, b);
}

template<typename n_t>
struct frac {
    n_t n, d;

    frac() : frac(0, 1) {}

    frac(n_t num, n_t den) {
        static_assert(std::is_integral<n_t>::value, "value type must be integral");
        if (den < 0) {
            n = -num;
            d = -den;
        } else {
            n = num;
            d = den;
        }
    }

    friend std::istream &operator>>(std::istream &in, frac<n_t> &rhs) {
        in >> rhs.x >> rhs.y;
        if (rhs.y < 0) {
            rhs.x = -rhs.x;
            rhs.y = -rhs.y;
        }
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const frac<n_t> &rhs) {
        out << rhs.n << "/" << rhs.d;
        return out;
    }

    // Returns the fraction in lowest terms
    frac lowest() const {
        n_t num = d < 0 ? -n : n;
        n_t den = d < 0 ? -d : d;
        return {num / gcd(num, den), den / gcd(num, den)};
    }

    frac operator+(const frac &r) const {
        if (d == r.d) return {n + r.n, d};

        n_t lcm = ::lcm(d, r.d);
        return {n * (lcm / d) + r.n * (lcm / r.d), lcm};
    }

    frac operator-(const frac &r) const {
        if (d == r.d) return {n - r.n, d};

        n_t lcm = ::lcm(d, r.d);
        return {n * (lcm / d) - r.n * (lcm / r.d), lcm};
    }

    frac operator*(const frac &r) const {
        return {n * r.n, d * r.d};
    }

    frac operator/(const frac &r) const {
        return {n * r.d, d * r.n};
    }

    bool operator==(const frac &r) const {
        if (d == r.d) return n == r.n;
        return n * r.d == r.n * d;
    }

    bool operator<=(const frac &r) const {
        if (d == r.d) return n <= r.n;
        return n * r.d <= r.n * d;
    }

    bool operator>=(const frac &r) const {
        if (d == r.d) return n >= r.n;
        return n * r.d >= r.n * d;
    }

    bool operator==(const n_t &r) const {
        if (d == 1) return n == r;
        return (n % d == 0) && n / d == r;
    }

    bool operator!=(const n_t &r) const {
        return !(*this == r);
    }

    bool is_zero() const {
        return n == 0;
    }
};

// Line representation in point-slope form, with fractional coords
template<typename n_t>
struct ln {
    frac<n_t> x, y, m;

    ln() : ln(0, 0, 0) {}

    ln(frac<n_t> x, frac<n_t> y, frac<n_t> m) : x(x), y(y), m(m) {
        static_assert(std::is_arithmetic<n_t>::value, "value type must be numeric");
    }

    frac<n_t> solve_x(const frac<n_t> &at_y) const {
        return (m * x + at_y - y) / m;
    }

    frac<n_t> solve_y(const frac<n_t> &at_x) const {
        return m * (at_x - x) + y;
    }
};

typedef frac<ll> fi;
typedef pair<fi, fi> pf;
typedef ln<ll> line;

void solve() {
    ll a, b, n;
    cin >> a >> b >> n;

    fi m(a, b);
    fi x(-1, 1);
    fi y(0, 1);

    rep(i, 0, n + 1) {
        if (m.is_zero()) {
            // I think we can assume we're on the left side here
            x = {1, 1};
            continue;
        }

        line u(x, y, m);
        fi nx, ny;

        if (y != 1) {
            nx = u.solve_x({1, 1});
            if (nx >= fi(-1, 1) && nx <= fi(1, 1)) {
                x = nx.lowest();
                y = {1, 1};
                m = {-m.n, m.d};
                continue;
            }
        }

        if (y != -1) {
            nx = u.solve_x({-1, 1});
            if (nx >= fi(-1, 1) && nx <= fi(1, 1)) {
                x = nx.lowest();
                y = {-1, 1};
                m = {-m.n, m.d};
                continue;
            }
        }

        if (x != -1) {
            ny = u.solve_y({-1, 1});
            if (ny >= fi(-1, 1) && ny <= fi(1, 1)) {
                x = {-1, 1};
                y = ny.lowest();
                m = {-m.n, m.d};
                continue;
            }
        }

        if (x != 1) {
            ny = u.solve_y({1, 1});
            if (ny >= fi(-1, 1) && ny <= fi(1, 1)) {
                x = {1, 1};
                y = ny.lowest();
                m = {-m.n, m.d};
                continue;
            }
        }
    }

    cout << x.n << " " << x.d << " " << y.n << " " << y.d << endl;
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
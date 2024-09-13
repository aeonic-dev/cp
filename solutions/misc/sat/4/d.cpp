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
#define gint() get_cin<int>()

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
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

    frac(n_t num) : frac(num, 1) {}

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
        if (n == 0 || d == 0) return {0, 1};

        n_t num = d < 0 ? -n : n;
        n_t den = d < 0 ? -d : d;
        return {num / gcd(num, den), den / gcd(num, den)};
    }

    frac operator+(const frac &r) const {
        if (n == 0 || d == 0) return r;
        if (r.n == 0 || r.d == 0) return *this;

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
        return frac(n * r.n, d * r.d).lowest();
    }

    frac operator/(const frac &r) const {
        return {n * r.d, d * r.n};
    }

    bool operator==(const frac &r) const {
        if (d == r.d) return n == r.n;
        return n * r.d == r.n * d;
    }

    bool is_zero() const {
        return n == 0;
    }

    pair<n_t, frac> mixed() const {
        return {
                n / d,
                {n % d, d}
        };
    }
};

typedef frac<ll> fi;

fi fpow(fi b, ll e) {
    if (e == 0) return {1, 1};
    if (e == 1) return b;

    return b * fpow(b, e - 1);
}

void fprint(fi f, bool newline = true) {
    f = f.lowest();

    if (f.d == 1) {
        cout << f.n;
        if (newline) cout << endl;

        return;
    }

    auto m = f.mixed();
    if (m.first >= 1) cout << m;
    else cout << f;

    if (newline) cout << endl;
}

void solve() {
    string s;
    cin >> s;
    reverse(all(s));

    fi sum(0, 1);
    fi mul(1, 1);
    rep(i, 0, s.size()) {
        int v = s[i] - '0';

        if (i == 0) sum = {v, 1};
        else {
            mul = mul * fi(3, 2);
            sum = sum + mul * v;
        }
    }

    fprint(sum);
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
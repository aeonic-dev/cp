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
int lcm(n_t a, n_t b) {
    if (a == 0 || b == 0) return 0;
    return a * b / __gcd(a, b);
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
        int num = d < 0 ? -n : n;
        int den = d < 0 ? -d : d;
        return {num / __gcd(num, den), den / __gcd(num, den)};
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
};

typedef frac<int> fi;
typedef frac<long> fl;
typedef frac<long long> fll;

void solve() {
    ll n, d;
    char tmp;
    cin >> n >> tmp >> d;

    fll f = {n, d};
    fll c = (f - fll(32, 1)) / fll(9, 5);
    cout << c.lowest() << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    solve();
}
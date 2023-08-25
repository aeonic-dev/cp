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
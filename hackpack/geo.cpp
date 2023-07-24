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

    friend std::istream &operator>>(std::istream &in, pt<n_t> &rhs) {
        in >> rhs.x >> rhs.y;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const pt<n_t> &rhs) {
        out << rhs.x << " " << rhs.y;
        return out;
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

    n_t theta() {
        return atan2(y, x);
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

    // Gets the unit vectors perpendicular to this one
    std::pair<pt, pt> perp() {
        n_t m = mag();
        return {{y / m,  -x / m},
                {-y / m, x / m}};
    }
};

template<typename n_t>
struct segment {
    pt<n_t> a, b;

    pt<n_t> direction() const {
        return b - a;
    }

    double distance(pt<n_t> v) {
        auto u = direction();
        return std::abs(u.cross(v) / u.mag());
    }

//    // Returns the intersection point or -1,-1 if there is none
//    pt intersection(segment s) {
//
//    }
};

// TODO: polygon; point in polygon (above/below cross with all segments that intersect)

template<typename n_t>
double area(const pt<n_t> &a, const pt<n_t> &b, const pt<n_t> &c) {
    return std::abs((b - a).cross(c - a)) / 2;
}
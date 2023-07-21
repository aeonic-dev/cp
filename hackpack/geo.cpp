template<typename n_t>
struct pt {
    n_t x, y;

    pt() : x(0), y(0) {
        static_assert(std::is_arithmetic<n_t>::value, "value type must be numeric");
    }

    pt(n_t x, n_t y) : x(x), y(y) {}

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

    pt unit() const {
        n_t m = mag();
        return {x / m, y / m};
    }

    // Projects the vector u onto this vector
    pt project(pt u) const {
        return unit() * dot(u) / mag();
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
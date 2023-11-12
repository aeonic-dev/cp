// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

//#pragma GCC target("avx2")
//#include <nmmintrin.h>

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

// meta macros
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define THANKS void GIVE_ME_A_SEMICOLON() // requires semicolon when calling a macro

// more aliases
#define pb push_back
#define eb emplace_back
#define mp make_pair

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

struct pt {
    double x, y;

    double distance(pt p) const {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

struct line {
    double a, b, c;

    line(double a, double b, double c) : a(a), b(b), c(c) {}

    line(pt p1, pt p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = a * p1.x + b * p1.y;
    }

    double determinant(line l) {
        return a * l.b - l.a * b;
    }

    pt intersection(line l) {
        double det = determinant(l);
        return {
                (l.b * c - b * l.c) / det,
                (a * l.c - l.a * c) / det
        };
    }
};

struct tri {
    pt p1, p2, p3;

    tri() = default;

    tri(pt p1, pt p2, pt p3) : p1(p1), p2(p2), p3(p3) {}

    double area() const {
        return round(
                (abs((p1.x * (p2.y - p3.y) +
                      p2.x * (p3.y - p1.y) +
                      p3.x * (p1.y - p2.y)) / 2.0) * 1000))
               / 1000;
    }

    double perimeter() const {
        return round(
                (p1.distance(p2) + p2.distance(p3) + p3.distance(p1)) * 1000)
               / 1000;
    }

    bool operator<(const tri &rhs) const {
        if (area() > rhs.area()) return true;
        if (area() < rhs.area()) return false;

        if (perimeter() > rhs.perimeter()) return true;
        return false;
    }
};

void solve() {
    cout << setprecision(3) << fixed;

    int zeroes;
    pt corners[4];

    while (true) {
        zeroes = 0;
        rep(i, 0, 4) {
            cin >> corners[i].x >> corners[i].y;
            if (corners[i].x == 0 && corners[i].y == 0) zeroes++;
        }
        if (zeroes == 4) break;

        line d1(corners[0], corners[2]);
        line d2(corners[1], corners[3]);
        pt center = d1.intersection(d2);

        tri quadrants[4];
        rep(i, 0, 4) {
            quadrants[i] = tri(corners[i], corners[(i + 1) % 4], center);
        }
        sort(quadrants, quadrants + 4);

        rep(i, 0, 4) cout << quadrants[i].area() << " " << quadrants[i].perimeter() << " ";
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}

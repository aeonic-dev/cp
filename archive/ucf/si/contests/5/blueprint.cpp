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

struct pt {
    int x, y;

    inline pt operator+(pt v) const {
        return {x + v.x, y + v.y};
    }

    inline pt operator-(pt v) const {
        return {x - v.x, y - v.y};
    }

    inline int cross(pt v) const {
        return x * v.y - y * v.x;
    }
};



bool intersects(vec<pt> &shape, pt v)

}

bool intersect(vec<pt> &a, vec<pt> &b) {
    travis(v, a) {
        if (intersects(b, v)) return true;
    }

    travis(v, b) {
        if (intersects(a, v)) return true;
    }

    return false;
}

void solve() {
    int b, n;
    cin >> b;

    bool flag = false;
    vec<vec<pt>> shapes(b);
    rep(i, 0, b) {
        cin >> n;
        shapes[i] = vec<pt>(n);

        rep(j, 0, n) {
            cin >> shapes[i][j].x >> shapes[i][j].y;
        }

        if (flag) continue;

        rep(j, 0, i) {
            if (intersect(shapes[i], shapes[j])) {
                cout << "Collision at " << i << ", " << j << endl;
                flag = true;
                break;
            }
        }
    }

    if (flag) {
        cout << "Bases Collide!\n";
    } else {
        cout << "Good to go!\n";
    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
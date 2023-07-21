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
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

double find_angle(double target, double min, double max, int depth) {
    double mid = min + (max - min) / 2;
    if (depth <= 0) return mid;

    double calc = mid - sin(mid);

    if (calc > target) return find_angle(target, min, mid, depth - 1);
    else return find_angle(target, mid, max, depth - 1);
}

// Finds the angle theta such that theta - sin(theta) = target
double find_angle(double target) {
    return find_angle(target, 0, 2 * M_PI, 100);
}

double degrees(double rad) {
    return rad * 180 / M_PI;
}

void solve() {
    int n, r;
    cin >> n >> r;

    if (n == 1) {
        cout << 90 << endl;
        return;
    }

    priority_queue<double, vec<double>, greater<double>> angles;
    double section_area = M_PI * r * r / (n + 1); // Target section_area of each section

    // Left and rightmost sections
    double theta_c = find_angle(section_area / (r * r / 2.0));
    double theta = theta_c / 2;
    angles.push(theta);
    angles.push(180 - theta);
    n -= 2;

    double last_angle = 180 - theta;
    if (n > 0) {
        // Angle spanning the section we have yet to place lines in
        double span = 180 - theta * 2;
        while (n > 0) {

        }
    }

//    rep(i, 0, n + 2) {
//        cout << angles.top() << endl;
//        angles.pop();
//    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)
    cout << setprecision(4) << fixed;

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}
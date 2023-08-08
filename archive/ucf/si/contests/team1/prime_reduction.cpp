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

void factorize(vec<pi> &factors, int a, int b) {
    int i = 2;

    while (i * i <= a) {
        int e = 0;
        while (a % i == 0) {
            a /= i;
            e++;
        }

        if (e > 0) factors.eb(i, e * b);
        i++;
    }

    if (a > 1) factors.eb(a, b);
}

vec<pi> factors;

void solve() {
    while (true) {
        int n;
        cin >> n;

        if (n == 4) return;

        int num = 0;
        while (true) {
            num++;
            factors.clear();
            factorize(factors, n, 1);

            if (factors[0].first == n) break;

            n = 0;
            for (auto f: factors) n += f.first * f.second;
            cout << endl;
        }

        cout << factors[0].first << " " << num << endl;
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
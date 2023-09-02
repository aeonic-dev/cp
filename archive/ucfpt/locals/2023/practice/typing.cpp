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

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
// @formatter:on

bool adj(char ch1, char ch2) {
    return (
            (ch1 != 'a' && ch1 != 'j' && ch1 != 's' && ch1 - 1 == ch2) ||
            (ch1 != 'i' && ch1 != 'r' && ch1 != 'z' && ch1 + 1 == ch2) ||

            (ch1 > 'i' && ch1 - 9 == ch2) ||
            (ch1 > 'i' && ch1 - 8 == ch2) ||
            (ch1 > 'j' && ch1 - 10 == ch2) ||

            (ch1 < 'r' && ch1 + 9 == ch2) ||
            (ch1 <= 'r' && ch1 + 8 == ch2) ||
            (ch1 < 'q' && ch1 + 10 == ch2)
    );
}

void solve() {
    string a, b;
    cin >> a >> b;

    if (a == b) {
        cout << 1 << endl;
        return;
    }

    if (a.size() == b.size()) {
        bool two = true;
        rep(i, 0, a.size()) {
//            cout << a[i] << " " << b[i] << " " << adj(a[i], b[i]) << endl;
            if (!(a[i] == b[i] || adj(a[i], b[i]))) two = false;
        }

        if (two) {
            cout << 2 << endl;
            return;
        }
    }

    cout << 3 << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
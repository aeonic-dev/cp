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

map<string, int> months{
        {"Jan", 0},
        {"Feb", 1},
        {"Mar", 2},
        {"Apr", 3},
        {"May", 4},
        {"Jun", 5},
        {"Jul", 6},
        {"Aug", 7},
        {"Sep", 8},
        {"Oct", 9},
        {"Nov", 10},
        {"Dec", 11},
};

struct date {
    int month;
    int day;
    int year;

    bool operator>(const date &rhs) const {
        if (year > rhs.year) return true;
        if (year < rhs.year) return false;

        if (month > rhs.month) return true;
        return month == rhs.month && day > rhs.day;
    }
};

const date bread{6, 7, 1928};

void solve() {
    int n;
    cin >> n;

    string best;
    auto max = DBL_MIN;
    rep(i, 0, n) {
        string name, m;
        cin.ignore();
        getline(cin, name);
        cin >> m;

//        cout << name << " " << m;

        date d{};
        d.month = months[m];
        cin >> d.day;
        cin.ignore();
        cin >> d.year;

        double val;
        cin >> val;

        if (val > max && d > bread) {
            max = val;
            best = name;
        }
    }

    cout << best << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

//    cout << setprecision(8) << fixed;
    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
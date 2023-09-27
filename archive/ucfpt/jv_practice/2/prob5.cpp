x// Settings
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
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
// @formatter:on

vec<string> ones_names{
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

string ones(char s) {
    return ones_names[s - '1'];
}

string tens(char t, char u) {
    switch (t) {
        case '1':
            switch (u) {
                case '0':
                    return "ten";
                case '1':
                    return "eleven";
                case '2':
                    return "twelve";
                case '3':
                    return "thirteen";
                case '5':
                    return "fifteen";
                case '8':
                    return "eighteen";
                default:
                    return ones(u) + "teen";
            }
        case '2':
            if (u == '0') return "twenty";
            return "twenty " + ones(u);
        case '3':
            if (u == '0') return "thirty";
            return "thirty " + ones(u);
        case '4':
            if (u == '0') return "forty";
            return "forty " + ones(u);
        case '5':
            if (u == '0') return "fifty";
            return "fifty " + ones(u);
        case '8':
            if (u == '0') return "eighty";
            return "eighty " + ones(u);
        default:
            if (u == '0') return ones(t) + "ty";
            return ones(t) + "ty " + ones(u);
    }
}

vec<string> places{
        "hundred", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion"
};

void solve() {
    int n;
    cin >> n;

    rep(i, 0, n) {
        string s;
        cin >> s;

        rep(i, 0, s.size() % 3) s = '0' + s;
        int p = s.size() / 3, j = s.size() % 3 - 3;

        while (j+=3, p--) {
            char a = s[j], b = s[j + 1], c = s[j + 2];
            if (a == '0' && b == '0' && c == '0') continue;
            if (j > 0) cout << " ";

            if (a != '0') {
                cout << ones(a) << " " << "hundred";
            }

            if (b != '0') {
                if (a != '0') cout << " ";
                cout << tens(b, c);
            }

            else if (c != '0') {
                if (a != '0') cout << " ";
                cout << ones(c);
            }

            if (p > 0) cout << " " << places[p];
        }

        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

//    int tests;
//    cin >> tests;
//    while (tests--) solve();
    solve();
}
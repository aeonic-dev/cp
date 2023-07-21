// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#pragma GCC target("avx2")

#include <nmmintrin.h>
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

__m128i min(__m128i port) {
    __m128i min = port;

    min = _mm_min_epu8(min, _mm_alignr_epi8(min, min, 0b0001));
    min = _mm_min_epu8(min, _mm_alignr_epi8(min, min, 0b0010));
    min = _mm_min_epu8(min, _mm_alignr_epi8(min, min, 0b0100));
    min = _mm_min_epu8(min, _mm_alignr_epi8(min, min, 0b1000));

    return min;
}

map<string, int> elements;

void solve() {
    int p, c, n;
    cin >> p >> c >> n;

    vec<__m128i> ports(p);
    vec<char> element(c);
    vec<int> levels(c);
    vec<int> damage(c);
    multimap<int, int> port_map;

    int temp[4];
    rep(i, 0, p) {
        rep(j, 0, 4) cin >> temp[i];
        ports[i] = _mm_loadu_si128((__m128i *) temp);
    }

    string t;
    rep(i, 0, c) {
        cin >> t >> levels[i] >> damage[i];
        element[i] = elements[t];
    }

    int p1, p2;
    rep(i, 0, n) {
        cin >> p1 >> p2;
        port_map.emplace(p1, p2);
    }
}

int main() {
    elements["air"] = 0;
    elements["earth"] = 1;
    elements["fire"] = 2;
    elements["water"] = 3;

    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
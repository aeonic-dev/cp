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
#define numeric(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

struct node {
    int l, r;
    ll lazy, max;
    node *left, *right;

    node(int l, int r) : l(l), r(r), lazy(0), max(0), left(nullptr), right(nullptr) {}

    ~node() {
        delete left;
        delete right;
    }

    void increment(int l, int r, int amt);

    void push();

    ll get_max();
};

void node::increment(int l, int r, int amt) {
    if (l > this->r || r < this->l) return;
    if (l <= this->l && r >= this->r) {
        lazy += amt;
        max += amt;
        return;
    }

    push();
    left->increment(l, r, amt);
    right->increment(l, r, amt);
    max = ::max(left->max, right->max);
}

void node::push() {
    if (left == nullptr) left = new node(l, (l + r) / 2);
    if (right == nullptr) right = new node((l + r) / 2 + 1, r);

    if (lazy != 0) {
        left->increment(l, r, lazy);
        right->increment(l, r, lazy);
        lazy = 0;
    }
}

ll node::get_max() {
    push();
    return max;
}

void solve() {
    int n, q, l, r, h;
    cin >> n >> q;

    node *root = new node(1, n);
    rep(i, 0, q) {
        cin >> l >> r >> h;
        root->increment(l, r, 1);
        cout << (root->get_max() < h ? "hit" : "blocked") << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
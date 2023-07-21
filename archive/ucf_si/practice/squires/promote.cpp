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
#define mp make_pair

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

struct node {
    node *parent;
    vec<node *> children;
    int index;

    node(node *parent, int index);

    ~node() {
        rep(i, 0, children.size()) delete children[i];
    }
};

node *nodes[100000];

node::node(node *parent, int index) : parent(parent), index(index) {
    nodes[index] = this;
}

void solve() {
    int n, m;
    cin >> n;

    vec<int> p(n);
    rep(i, 0, n) cin >> p[i];

    int index = 0;
    node *root = new node(nullptr, index++);

    vec<int> out(n, 0);
    rep(i, 0, n - 1) {
        cin >> m;
        nodes[m - 1]->children.push_back(new node(nodes[m - 1], index++));

        node *ch = nodes[m - 1]->children.back(), *cur = ch->parent;
        while (cur != nullptr) {
            if (p[cur->index] <= p[i]) out[cur->index]++;
            cur = cur->parent;
        }
    }

    rep(i, 0, n) cout << out[i] << endl;

    delete root;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}
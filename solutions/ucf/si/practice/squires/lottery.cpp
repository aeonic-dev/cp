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

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

namespace trie {
    struct node {
        node *children[26]{};
        bool is_valid_word;
        int valid_paths;

        node() : is_valid_word(false), valid_paths(0) {}

        ~node() {
            for (int i = 0; i < 26; i++) delete children[i];
        }

    public:
        void add(string s) {
            node *cur = this;

            for (int i = 0; i < s.size(); i++) {
                cur->valid_paths++;
                if (cur->children[s[i] - 'a'] == nullptr) cur->children[s[i] - 'a'] = new node();
                cur = cur->children[s[i] - 'a'];
            }

            cur->valid_paths++;
            cur->is_valid_word = true;
        }

        int count_prefix(string s) {
            node *cur = this;

            for (int i = 0; i < s.size(); i++) {
                if (cur->children[s[i] - 'a'] == nullptr) return 0;
                cur = cur->children[s[i] - 'a'];
            }

            return cur->valid_paths;
        }

        int count_pairs() {
            if (valid_paths < 2) return 0;
            if (valid_paths == 2) return 1;

            int num = 0;
            for (int i = 0; i < 26; i++) {
                if (children[i] != nullptr) num += children[i]->count_pairs();
            }

            return num;
        }
    };

    class string_trie {
        node *root;

    public:
        string_trie() : root(new node()) {}

        ~string_trie() {
            delete root;
        }

        void add(string s) {
            root->add(s);
        }

        int count_prefix(string s) {
            return root->count_prefix(s);
        }

        void flip() {
            node *new_root = new node();

        }
    };
}

using namespace trie;

int n = 0;

void solve() {
    int q, t;
    cin >> q;

    cout << "Lottery #" << ++n << ":\n";

    bool flipped = false;
    string s;
    string_trie forw, back;

    rep(i, 0, q) {
        cin >> t;
        switch (t) {
            case 1:
                cin >> s;

                (flipped ? back : forw).add(s);
                reverse(all(s));
                (flipped ? forw : back).add(s);

                break;
            case 2:
                cin >> s;
                cout << (flipped ? back : forw).count_prefix(s) << endl;
                break;
            case 3:
                flipped = !flipped;
                break;
        }
    }

    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/milk_time)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
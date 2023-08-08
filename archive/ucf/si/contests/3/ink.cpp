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
        node *parent;
        node *children[26]{};
        li num_children;
        li word_count;
        li valid_paths;
        int depth;

        node(node *parent) : parent(parent), num_children(0), word_count(0), valid_paths(0), depth(0) {}

        node(node *parent, int depth) : parent(parent), num_children(0), word_count(0), valid_paths(0), depth(depth) {}

        ~node() {
            for (int i = 0; i < 26; i++) delete children[i];
        }

    public:
        void add(string s);

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

        ll sum_similarities() {
            li num = (word_count == 0) ? 0 : depth * (word_count * (word_count - 1) / 2);
            if (num_children == 0) return num;

            if (num_children == 1) {
                rep(i, 0, 26) {
                    if (children[i] != nullptr) {
                        auto paths = valid_paths + word_count;
                        auto child_paths = (children[i]->valid_paths + children[i]->word_count);

                        num += child_paths * (paths - child_paths) * depth;
                        return num + children[i]->sum_similarities();
                    }
                }
            }

            // Multiple children
            li checked_paths = 0;
            rep(i, 0, 26) {
                if (children[i] != nullptr) {
                    auto paths = valid_paths + word_count;
                    auto child_paths = (children[i]->valid_paths + children[i]->word_count);

                    checked_paths += child_paths;
                    num += child_paths * (paths - checked_paths) * depth;
                    num += children[i]->sum_similarities();
                }
            }

            return num;
        }
    };

    class string_trie {
        node *root;

    public:
        string_trie() : root(new node(nullptr)) {}

        ~string_trie() {
            delete root;
        }

        void add(string s) {
            root->add(s);
        }

        int count_prefix(string s) {
            return root->count_prefix(s);
        }

        ll sum_similarities() {
            return root->sum_similarities();
        }
    };
}

trie::node *words[100001];

void trie::node::add(std::string s) {
    node *cur = this;
    li cur_depth = depth + 1;

    for (int i = 0; i < s.size(); i++) {
        cur->valid_paths++;
        if (cur->children[s[i] - 'a'] == nullptr) {
            cur->children[s[i] - 'a'] = new node(cur, cur_depth);
            cur->num_children++;
        }
        cur = cur->children[s[i] - 'a'];
        cur_depth++;
    }

    cur->word_count++;
}

void solve() {
    int w;
    cin >> w;

    trie::string_trie trie;

    string s;

    rep(i, 0, w) {
        cin >> s;
        for (auto &c: s) c = tolower(c);
        trie.add(s);
    }

    cout << trie.sum_similarities() << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}
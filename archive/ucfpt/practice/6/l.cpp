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
#define gin(type) get_cin<type>()

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
// @formatter:on

vector<vector<int>> board;
vector<vector<char>> res;

int h, w;
int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

bool isValid(int x, int y) {
    return x > 0 && y > 0 && x < h + 1 && y < w + 1;
}

void solve() {
    cin >> h >> w;

    board = vector<vector<int>>(h + 2, vector<int>(w + 2));
    res = vector<vector<char>>(h + 2, vector<char>(w + 2, 'Y'));

    for (int i = 0; i < h + 2; i++) {
        for (int j = 0; j < w + 2; j++) {
            cin >> board[i][j];
        }
    }

    bool change = true;

    while (change) {
        change = false;
        for (int i = 0; i < h + 2; i++) {
            for (int j = 0; j < w + 2; j++) {
                int fillsNeeded = board[i][j];
                int fills = 0;
                queue<pair<int, int>> q;
                queue<pair<int, int>> flags;

                for (int k = 0; k < 9; k++) {
                    if (isValid(i + dx[k], j + dy[k])) {
                        if (res[i + dx[k]][j + dy[k]] == 'Y') {
                            fills++;
                            q.push({i + dx[k], j + dy[k]});
                        } else {
                            if (res[i + dx[k]][j + dy[k]] == 'X') fillsNeeded--;
                        }
                    }
                }

                if (fills == fillsNeeded) {
                    while (q.size()) {
                        auto p = q.front();
                        q.pop();
                        res[p.first][p.second] = 'X';
                        change = true;
                    }
                } else if (fillsNeeded == 0) {
                    auto p = q.front();
                    q.pop();
                    res[p.first][p.second] = '.';
                    change = true;
                }
            }
        }

    }

    bool f = true;

    for (int i = 0; i < h + 2; i++) {
        for (int j = 0; j < w + 2; j++) {
            int fillsNeeded = board[i][j];
            int fills = 0;

            for (int k = 0; k < 9; k++) {
                if (isValid(i + dx[k], j + dy[k]) && res[i + dx[k]][j + dy[k]] == 'X') {
                    fills++;
                }
            }

            if (fills != fillsNeeded) {
                f = false;
            }
        }
    }

    if (f) {
        for (int i = 1; i < h + 1; i++) {
            for (int j = 1; j < w + 1; j++) {
                cout << res[i][j];
            }
            cout << endl;
        }
    } else {
        cout << "impossible" << endl;
    }
}

#define MULTIPLE_CASES 0
int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)
#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}
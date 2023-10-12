#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long int li;
typedef long double ld;

#define vec vector
#define pb push_back
#define eb emplace_back
#define rep(i, s, e) for (int i = s; i < e; i++)
#define trav(x, s) for (auto &x : s)

int main() {
    int n;
    string s;
    cin >> n >> s;

    vec<vec<char>> msg(n, vec<char>(n, '#'));

    int m = n / 2, r = m, c = m;  // m = max row/col index for cur rad.
    rep(i, 0, s.size()) {
        msg[r][c] = s[i];

        if (r == n - m - 1) {
            if (c == n - m - 1) {
                // next circle
                r--;
                m++;
            } else {
                if (c == m) r++;
                else c++;
            }
        } else {
            if (r == m) {
                if (c == n - m - 1) r--;
                else c--; 
            } else {
                if (c == n - m - 1) r--;
                else r++;
            }
        }
    }

    trav(r, msg) trav(c, r) if (c != '#') cout << c;

    return 0;
}
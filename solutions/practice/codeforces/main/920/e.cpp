#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int h, w, ax, ay, bx, by;
    cin >> h >> w >> ax >> ay >> bx >> by;

    if (bx - ax <= 0) {
        cout << "Draw\n";
        return;
    }

    int m = 1; // who just moved (0 = alice, 1 = bob)
    while (bx - ax > 0) {
        m = !m;
        if (!m) {
            // alice's move
            if (abs(bx - ax) % 2) {
                // attack
                if (by - ay > 0) ay++;
                else if (by - ay < 0) ay--;
            } else {
                // avoid
                if (by - ay < 0) {
                    if (ay < w) ay++;
                } else if (by - ay > 0) {
                    if (ay > 1) ay--;
                }
            }

            ax++;
        } else {
            // bob's move
            if (abs(bx - ax) % 2) {
                // attack
                if (ay - by > 0) by++;
                else if (ay - by < 0) by--;
            } else {
                // avoid
                if (ay - by < 0) {
                    if (by < w) by++;
                } else if (ay - by > 0) {
                    if (by > 1) by--;
                }
            }

            bx--;
        }
    }

    if (ay != by) cout << "Draw\n";
    else {
        cout << (m ? "Bob" : "Alice") << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

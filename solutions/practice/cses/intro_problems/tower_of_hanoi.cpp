#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void mv(vec<stack<int>> &piles, int from, int to) {
    if (piles[from].empty() ||
        (piles[to].size() && piles[from].top() > piles[to].top()))
        swap(from, to);

    piles[to].push(piles[from].top()), piles[from].pop();
    cout << from + 1 << " " << to + 1 << endl;
}

void solve() {
    int n;
    cin >> n;

    int m = (1 << n) - 1;
    cout << m << endl;

    vec<stack<int>> piles(3);
    for (int i = n; i > 0; i--) piles[0].push(i);

    int a = 0, b = 1, c = 2;
    if (n % 2 == 0) swap(b, c);

    rep(i, 1, m + 1) {
        mv(piles, (i % 3) ? a : b, (i % 3 == 2) ? b : c);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

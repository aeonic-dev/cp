#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n;
    cin >> n;
    queue<int> q;
    rep(i, 0, n) q.push(i + 1);

    bool take = false;
    while (!q.empty()) {
        if (take) cout << q.front() << " ";
        else q.push(q.front());

        q.pop();
        take = !take;
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

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;;

const int mod = 1'000'000;
void solve() {
    int a, b, c, t;
    cin >> a >> b >> c >> t;
    vi dist(mod, INT_MAX);
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();
        if (dist[u] < INT_MAX) continue;
        dist[u] = d;
        
        q.emplace((u + a) % mod, d + 1);
        q.emplace((u * b) % mod, d + 1);
        q.emplace((u / c) % mod, d + 1);
    }
    
    int res = dist[t];
    if (res == INT_MAX) cout << "-1\n";
    else cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}

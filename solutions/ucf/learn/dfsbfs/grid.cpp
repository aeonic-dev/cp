#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vi> gr(n, vi(m)), dist(n, vi(m, INT_MAX));
    rep(i, 0, n) {
        string str;
        cin >> str;
        rep(j, 0, m) gr[i][j] = str[j] - '0';
    }
    queue<tuple<int, int, int>> q;
    q.emplace(0, 0, 0);
    while (!q.empty()) {
        auto [i, j, d] = q.front();
        q.pop();
        if (i < 0 || i >= n || j < 0 || j >= m) continue;
        if (dist[i][j] < INT_MAX) continue;
        dist[i][j] = d;
        
        int t = gr[i][j];
        q.emplace(i + t, j, d + 1);
        q.emplace(i - t, j, d + 1);
        q.emplace(i, j + t, d + 1);
        q.emplace(i, j - t, d + 1);
    }
    
    int res = dist[n - 1][m - 1];
    if (res == INT_MAX) cout << "-1\n";
    else cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}

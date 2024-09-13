#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, m, d_l;
    cin >> n >> m;

    vi mes(n), cln(n);
    rep(i, 0, n) cin >> mes[i] >> cln[i];

    bitset<1'000> vis;
    rep(i, 0, m) {
        cin >> d_l, vis[--d_l] = true;
    }

    priority_queue<pair<bool, int>> pq; // {used, cln}
    int res = 0;
    for (int i = d_l; i >= 0; i--) {
        int mess = mes[i];
        // cout << "\nday " << i + 1 << "\n";
        if (vis[i]) {
            // need to clean today; can't use any cleaning on future days
            while (!pq.empty()) pq.pop();
            if (mess) {
                if (cln[i] >= mess) {
                    // cout << "cleaning\n";
                    pq.emplace(1, cln[i] - mess);
                    res++;
                    continue;
                }
                // impossible to clean today
                return void(cout << -1 << '\n');
            }
        }
        pq.emplace(0, cln[i]);
        while (!pq.empty() && mess) {
            auto [used, clean] = pq.top();
            pq.pop();
            if (!clean) continue; // skip empty cleaning
            res += !used;
            if (mess >= clean) mess -= clean;
            else {
                clean -= mess, mess = 0;
                pq.emplace(1, clean);
            }
        }
        if (mess) return void(cout << -1 << '\n');
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

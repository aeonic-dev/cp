#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, a, b;
    cin >> n;

    vec<tuple<int, bool, int>> e; // {time, is_leaving, id}
    e.reserve(n * 2);
    rep(i, 0, n) {
        cin >> a >> b;
        e.emplace_back(a, 0, i);
        e.emplace_back(b, 1, i);
    }
    sort(all(e));

    int max = 1;
    set<int> rooms{1};
    map<int, int> at;
    vec<int> r(n);

    for (auto evt : e) {
        int p = get<2>(evt); // person

        if (get<1>(evt)) {
            // leaving

            rooms.insert(at[p]);
            at.erase(p);

            continue;
        }

        // arriving

        if (rooms.empty()) rooms.insert(++max);
        int rm = *rooms.begin();

        rooms.erase(rm);
        r[p] = at[p] = rm;
    }

    cout << max << "\n";
    for (auto rm : r) cout << rm << " ";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}

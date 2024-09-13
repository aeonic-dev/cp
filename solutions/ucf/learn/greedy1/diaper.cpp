#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

int tc = 0;
void solve() {
    int n, d;
    cin >> n >> d;
    vector<tuple<int, double, int>> dias(d); // {num, price, capacity}
    for (auto &[num, p, cap] : dias) cin >> num >> p >> cap;

    vi shits(n);
    for (int &shit : shits) cin >> shit;
    int max_shit = accumulate(all(shits), 0,
                              [](int a, int b) { return max(a, b); });

    int best = -1;
    double res = DBL_MAX;
    rep(i, 0, d) {
        auto [num_per, price, cap] = dias[i];
        if (max_shit > cap) continue;

        ll cur = 0, num = 0;
        for (int shit : shits) {
            if (cur + shit > cap) cur = shit, num++;
            else cur += shit;
        }
        if (cur) num++;

        double cost = price * (num / num_per + bool(num % num_per));
        if (cost < res) res = cost, best = i;
    }

    cout << setprecision(2) << fixed
         << "Diaper Scenario #" << ++tc
         << ": Buying box " << best + 1
         << ", you spend $" << res
         << ".\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

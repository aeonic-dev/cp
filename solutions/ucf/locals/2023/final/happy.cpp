#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define pb push_back
#define eb emplace_back
#define rep(i, s, e) for (int i = s; i < e; i++)
#define trav(x, s) for (auto &x : s)

struct customer {
    int num, arrival, service, patience;
};

int main() {
    int n;
    cin >> n;

    vec<int> happy;
    happy.reserve(n);

    queue<customer> q;
    rep(i, 0, n) {
        customer c;
        cin >> c.num >> c.arrival >> c.service >> c.patience;
        q.push(c);
    }

    int t = -1;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        int deadline = cur.arrival + cur.patience;
        if (t > deadline) continue;

        if (cur.arrival > t) t = cur.arrival;
        t += cur.service;
        happy.pb(cur.num);
    }

    trav(x, happy) cout << x << endl;

    return 0;
}
// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// primitive types
typedef long long ll;
typedef long int li;

// aliases
#define vec vector
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// more aliases
#define pb push_back
#define eb emplace_back

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

struct task {
    ll r, c, d; // Time received, to complete, time due
};

struct receied_sooner {
    bool operator()(const task *a, const task *b) const {
        return a->r > b->r;
    }
};

struct due_sooner {
    bool operator()(const task *a, const task *b) const {
        return a->d > b->d;
    }
};

void solve() {
    int n;
    cin >> n;

    vec<task> tasks(n);
    priority_queue<task *, vec<task *>, receied_sooner> todo;
    rep(i, 0, n) {
        cin >> tasks[i].r >> tasks[i].c >> tasks[i].d;
        todo.push(&tasks[i]);
    }

    priority_queue<task *, vec<task *>, due_sooner> q;
    q.push(todo.top());
    ll done = 0;
    ll current_time = todo.top()->r;
    todo.pop();

    while (!todo.empty()) {
        task *new_task = todo.top();
        todo.pop();

        ll r = new_task->r;
        ll time_spent = r - current_time; // Time spent working from last received till now
        ll next_time = current_time + time_spent;

        while (!q.empty() && q.top()->c <= time_spent) {
            current_time += q.top()->c;
            time_spent -= q.top()->c;

            if (current_time <= q.top()->d) done++;

            q.pop();
        }

        if (!q.empty()) {
            q.top()->c -= time_spent;
        }

        q.push(new_task);
        current_time = next_time;
    }

    while (!q.empty()) {
        current_time += q.top()->c;
        if (current_time <= q.top()->d) done++;
        q.pop();
    }

    cout << done << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

//    solve();
    int tests;
    cin >> tests;
    while (tests--) solve();
}
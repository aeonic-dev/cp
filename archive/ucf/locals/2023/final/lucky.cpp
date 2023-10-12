#include <bits/stdc++.h>
using namespace std;

int main() {
    string n;
    cin >> n;

    int val = 0;
    bool has7 = false;
    for (auto &c : n) {
        int digit = c - '0';
        val *= 10;
        val += digit;

        if (digit == 7) has7 = true;
    }

    if (!has7) {
        if (val % 7 == 0) cout << 1;
        else cout << 0;
    } else {
        if (val % 7 == 0) cout << 3;
        else cout << 2;
    }
    
    return 0;
}
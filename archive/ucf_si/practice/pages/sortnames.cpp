#include <bits/stdc++.h>

using namespace std;

struct person {
    string name;
    int age;
    long int money;

    bool operator<(const person &rhs) const {
        if (money < rhs.money) return true;
        if (money > rhs.money) return false;

        return age > rhs.age;
    }
};

int main() {
    int n;
    cin >> n;

    vector<person> people(n);
    for (int i = 0; i < n; i++) cin >> people[i].name >> people[i].age >> people[i].money;
    sort(people.rbegin(), people.rend());

    for (int i = 0; i < n; i++) cout << people[i].name << " " << people[i].age << " " << people[i].money << endl;
}
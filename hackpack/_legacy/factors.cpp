// Compute prime factors of a^b
void factorize(vec<pair<int, int>> &factors, int a, int b) {
    int i = 2;

    while (i * i <= a) {
        int e = 0;
        while (a % i == 0) {
            a /= i;
            e++;
        }

        if (e > 0) factors.eb(i, e * b);
        i++;
    }

    if (a>1) factors.eb(a, b);
}
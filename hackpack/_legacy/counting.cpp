long long inverse(long long a, long long mod) {
    if (a == 1) return 1;
    return (mod - (mod / a) * inv(mod % a, mod)) % mod;
}
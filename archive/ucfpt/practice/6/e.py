import math

n = int(input())

pairs = []

mx = 0

for i in range(n):
    a,b = input().split()
    da, db = False, False
    afront, aback, bfront, bback = '', '', '', ''
    for c in a:
        if c == '.':
            da = True
        elif da:
            aback += c
        else:
            afront += c
    for c in b:
        if c == '.':
            db = True
        elif db:
            bback += c
        else:
            bfront += c
    while len(aback) != len(bback):
        if len(aback) > len(bback):
            bback += '0'
        else:
            aback += '0'
    a,b = int(afront + aback), int(bfront + bback)
    g = math.gcd(a,b)
    a,b = a//g, b//g
    pairs.append((a,b))

    if a > mx:
        mx = a
    if b > mx:
        mx = b

ip = [1] * (mx + 1)
ip[0], ip[1] = 0, 0
i = 2
while i * i <= mx:
    if ip[i]:
        for j in range(i * i, mx + 1, i):
            ip[j] = 0
    i += 1

for pair in pairs:
    a,b = pair
    if a == b:
        print(2,2)
    elif ip[a] and ip[b]:
        print(a,b)
    else:
        print('impossible')
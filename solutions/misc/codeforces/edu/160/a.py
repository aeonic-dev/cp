for i in range(int(input())):
    s = input()
    r = False
    for j in range(1, len(s)):
        a, b = s[:j], s[j:]
        if a[0] == '0' or b[0] == '0':
            continue
        if int(b) > int(a):
            r = True
            print(a, b)
            break

    if not r:
        print(-1)

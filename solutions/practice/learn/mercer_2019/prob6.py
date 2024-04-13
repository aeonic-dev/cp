for tc in range(int(input())):
    n = int(input())
    frogs = list(map(int, input().split()))
    frogs.sort()

    if (n == 2):
        print(0)
        continue

    gap_sum = 0
    for i in range(1, n):
        gap_sum += frogs[i] - frogs[i - 1] - 1
    min_gap = min(frogs[1] - frogs[0], frogs[-1] - frogs[-2]) - 1

    print(gap_sum - min_gap)

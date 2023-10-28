n = int(input())
hp = list(map(int, input().split()))
vp = list(map(int, input().split()))
win = False
train =0
while not win:
    for i in range(n):
        if hp[i] + train > vp[i]:
            win = True
            break
        elif hp[i] + train != vp[i]:
            break
        if i == n-1 and hp[i] + train == vp[i]:
            win = True
            break
    if not win:
        train += 1
print(train)
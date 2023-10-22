n = int(input())
nums = list(map(int, input().split()))
base = [0] * (n+1)
base[0] = nums[0]
for i in range(n):
    base[i+1] = nums[i] - base[i]
mno = 10 ** 8
mne = 10 ** 8
for i in range(n+1):
    if i % 2 == 0 and base[i] < mno:
        mno = base[i]
    elif base[i] < mne:
        mne = base[i]
print(max(0, mno + mne + 1))
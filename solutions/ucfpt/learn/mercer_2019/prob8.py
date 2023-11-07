sum = 0
i = 0
while True:
    i += 1
    ln = f"Line {i} = "
    nstr = ""
    words = input().split(' ')
    if (len(words) >= 2 and words[0] == "THE" and words[1] == "END"):
        break
    for word in words:
        nstr += str(len(word))
    sum += int(nstr)
    print(ln + nstr)
print("Sum of file = " + str(sum))

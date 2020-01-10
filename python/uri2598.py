for i in range(int(input())):
    N = [float(x) for x in input().split()]
    print('{:.0f}'.format(N[0]//N[1]+ int(not(not(N[0]%N[1])))))

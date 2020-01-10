cont=1
while True:
    N = float(input())
    if N == -1:
        break
    print("Experiment {:}: {:.0f} full cycle(s)".format(cont, N//2))
    cont+=1

def mdc(num,den):
    return mdc(den, num%den) if num%den else den

while True:
    try:
        d = [float(x) for x in input().split()]
        print('{:.0f}'.format(2*(d[0]+d[1])/mdc(d[0], d[1])))
    except EOFError:
        break

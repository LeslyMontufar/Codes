global a, b, n
def carry(posb):
    global n, a, b
    na = int(a[len(a)-1-((len(b)-1)-posb)])
    nb = int(b[posb])
    if na+nb > 9:
        n = n+1
        a = str(int(a) + nb*10**((len(b)-1)-posb))
    if posb:
        carry(posb-1)
while True:
    n = 0
    a, b = input().split()
    if a == '0' and b == '0':
      break  
    if a<b:
      aux = a
      a=b
      b=aux
    carry(len(b)-1) 
    if n:
      if n!=1:
        print(n, " carry operations.")
      else:
        print("1 carry operation.")
    else:
      print("No carry operation.")

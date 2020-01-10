def Rafael(x,y):
    return (3*x)**2+y**2
def Beto(x,y):
    return 2*(x**2)+(5*y)**2
def Carlos(x,y):
    return -100*x + y**3

for i in range(int(input())):
    [x,y] = [int(x) for x in input().split()]
    dic = {Rafael(x, y):'Rafael', Beto(x, y):'Beto', Carlos(x, y):'Carlos'}
    print(dic.get(max(dic.keys()))+' ganhou')

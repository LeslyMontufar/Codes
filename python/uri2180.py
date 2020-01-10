def isprime(n):
    div = n//2
    while (n%div):
        div-=1
    return 1 if div==1 else 0

# from matplotlib import pyplot as plt
aux = w = int(input())
vel = 0
for i in range(10):
    while not(isprime(aux)):
        aux+=1
    vel+=aux
    aux+=1
print(vel, 'km/h')
print('{:.0f} h / {:.0f} d'.format(60e6//vel,60e6//(vel*24)))

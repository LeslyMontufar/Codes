def readfile(arq):
    for linha in arq:
        linha = linha.strip()
        lista.append(linha)
    return lista

from os import sys
import random
print('Choose:\n\t0 - bye bye\n\t1 - read\n\t2 - insert new activity', end='')
print('\n\t3 - activities qtd\n\t4 - delete an activity')

while True:
    op = int(input('\n(choose an option)>>> '))
    if op:
        lista = []
        with open('Les activités.txt', 'r') as arq:
            lista = readfile(arq) 
    else:
        break
    
    if op == 1:
        print('Reading ...\n')
        for i in lista:
            print(i)
    elif op == 2:
        new = input('(new activity)>>> ')
        with open('Les activités.txt', 'a') as arq:
            arq.write(str(random.randrange(0, len(lista))) + ' - ' + new + '\n')
    elif op == 3:
        print('Counting ...\n')
        print('>>> There\'re '+str(len(lista))+' registered activities.')
    elif op == 4:
        sys('help')        

coelhos = ratos = sapos = 0
for i in range(int(input())):
    entrada = input().split()
    entrada[0] = eval(entrada[0])
    if entrada[1] == 'C':
        coelhos = coelhos + entrada[0]
    elif entrada[1] == 'R':
        ratos = ratos + entrada[0]
    elif entrada[1] == 'S':
        sapos = sapos + entrada[0]
total = coelhos+ratos+sapos
print('Total: {total} cobaias'.format(total))
print('Total de coelhos: {:}'.format(coelhos))
print('Total de ratos: {:}'.format(ratos))
print('Total de sapos: {:}'.format(sapos))
print('Percentual de coelhos: {:.2f} %'.format(coelhos/total*100))
print('Percentual de ratos: {:.2f} %'.format(ratos/total*100))
print('Percentual de sapos: {:.2f} %'.format(sapos/total*100))

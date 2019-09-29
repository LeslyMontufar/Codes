arq = open('C:\\Users\\lesly\\Documents\\weird-unsorted-data.txt', 'r')
print('Posição atual no arquivo: ' + str(arq.tell()))
i=1
while arq.seek(43210*i):
    if arq.read(1)!="#":
        print(arq.read(1), end="")
    i=i+1
print('Posição atual no arquivo: ' + str(arq.tell()))
arq.close()

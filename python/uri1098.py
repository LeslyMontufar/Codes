i = 0
j = 1
while i <= 2:
    j = 1 + i
    while j < 4 + i:
        print('I={:} J={:}'.format(str(round(i, 2)).rstrip('0').rstrip('.') if not(isinstance(round(i, 2), int)) else round(i, 2),
                                   str(round(j, 2)).rstrip('0').rstrip('.') ))
        j = j + 1
    i = i + 0.2

while True:
    entrada = input().split()
    if entrada == ['0', '0']:
        break
    print(int(entrada[1].replace(entrada[0],'')) if entrada[1].replace(entrada[0],'')!='' else 0)

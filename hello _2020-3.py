import matplotlib.pyplot as plt

def testar(R1,X1,Y1,R2,X2,Y2):
    pontosteste = [[X2+R2,Y2],[X2-R2,Y2],[X2,Y2+R2],[X2,Y2-R2]]
    for [x,y] in pontosteste:
        if (x-X1)**2+(y-Y1)**2 > R1**2:
            return "MORTO"
    return "RICO"
while True:
    try:
        [R1,X1,Y1,R2,X2,Y2] = [int(x) for x in input().split()]
        if not R1:
            break
        print(testar(R1,X1,Y1,R2,X2,Y2))
        
        plt.style.use('ggplot')
        fig, ax = plt.subplots()
        ax.add_patch(plt.Circle((X1, Y1), R1, color='r', alpha=0.5))
        ax.add_patch(plt.Circle((X2, Y2), R2, color='#19A0FF', alpha=0.5))
        ax.set_aspect('equal', adjustable='datalim')
        ax.plot()   #Causes an autoscale update.
        plt.show()

    except EOFError:
        break
    
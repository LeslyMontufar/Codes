import turtle
import random

w, h = [500, 500]
nturtles = 8
step = 20
turtle.screensize(w, h) # turtle is a standalone tool for doing graphics

screen = turtle.Screen()
screen.title("Turtle Race!")

image = {'back': "flags.png"}

class racer(object):
        ## Constructer
        def __init__(self, color, pos): # constructer
                self.color = color
                self.pos = pos
                #now about the turtle:
                self.tinfo = turtle.Turtle()
                self.tinfo.shape('turtle')
                self.tinfo.color(color)
                self.tinfo.penup() # no drawing when moving
                self.tinfo.setpos(pos)
                self.tinfo.setheading(90) # 90 graus, para que olhe para cima
                self.tinfo.pensize(6)

        def move(self): # method exe pelo object
                r = random.randrange(1, step)
                self.pos = (self.pos[0], self.pos[1] + r)
                self.tinfo.pendown() # pen down
                self.tinfo.forward(r) # anda uma vez

##        def listen(self, direction)
##                screen.onkey(forward, "Up")
##                screen.onkey(backward, "Down")
##                screen.onkey(left, "Left")
##                screen.onkey(right, "Right")
##                screen.listen()
        
def startGame():
        ## Ambiente
        turtle.clearscreen()
        screen.bgpic(image['back'])
        
        ## Objects
        tList = [] ## lista de racers, que tbm sao turtles, cada tList[2 ...] é um racer
        colors = ["red", "green", "blue", 'yellow', 'pink', 'orange', 'purple', 'black', 'grey']
        start = -h/2 +20 # lugar da 1a turtle
        
        for t in range(nturtles):
                tList.append(racer(colors[t], (start+t*((w-40)//(nturtles-1)), start)))

        run = True
        while run:
                # passo de cada vez
                for t in tList:
                        t.move()
                # alguem perto de ganhar?
                for t in tList:
                        if t.pos[1] > h/2 - step - 20:
                                t.pos = h/2 - 20
                                run = False

while True:
        startGame()



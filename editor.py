
class Vect:

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def echo(self):
        return str(self.x) + " "+ str(self.y) +" "+str(self.z)

def add(A, B):
    return Vect(A.x + B.x, A.y + B.y, A.z + B.z)


class t3D:
    def __init__(self, A, B, C):
        self.A = A
        self.B = B
        self.C = C 
        self.color = [255, 255, 255]
    
    def echo(self):
        return self.A.echo() + " - " + self.B.echo() + " - " + self.C.echo() + " - r" + str(self.color[0]) + " g" + str(self.color[1]) +  " b" + str(self.color[2]) +"\n"


class rectangle:
    def __init__(self, A, B, C, D, color=[255,255,255]):
        self.t1 = t3D(A, B, C)
        self.t2 = t3D(A, D, C)
        self.t1.color = color
        self.t2.color = color
    def echo(self):
        return self.t1.echo() + self.t2.echo()

    

class couloir1:
    def __init__(self, position, color=[255, 255, 255]):
        self.ensemble = []
        A = add(position, Vect(0, 0, 0))
        B = add(position, Vect(10, 0, 0))
        C = add(position, Vect(0, 0, 20))
        D = add(position, Vect(10, 0, 20))
        G = add(position, Vect(0, 20, 0))
        H = add(position, Vect(10, 20, 0))
        E = add(position, Vect(0, 20, 20))
        F = add(position, Vect(10, 20, 20))
        I = add(position, Vect(0, 0, 0))
        J = add(position, Vect(10, 0, 0))
        K = add(position, Vect(0, 0, 20))
        L = add(position, Vect(10, 0, 20))
        M = add(position, Vect (0, 0, 10))
        N = add(position, Vect(10, 0, 10))
        O = add(position, Vect(0, 20, 10))
        P = add(position, Vect(10, 20, 10))
        self.R1 = rectangle(A, M, N, B, color)
        self.R2 = rectangle(M, C, D, N, color)
        self.R3 = rectangle(C, D, L, K, color)
        self.R4 = rectangle(K, L, F, E, color)
        self.R5 = rectangle(E, F, P, O, color)
        self.R6 = rectangle(O, P, H, G, color)
        self.R7 = rectangle(H, G, I, J, color)
        self.R8 = rectangle(I, J, B, A, color)

    def echo(self):
        return self.R1.echo() + self.R2.echo() + self.R3.echo() + self.R4.echo() + self.R5.echo() + self.R6.echo() + self.R7.echo() + self.R8.echo()


monde = ""

grey = [180, 180, 180]

for i in range(5):
    monde += couloir1(Vect(i*20, 0, 0)).echo()
    monde += couloir1(Vect(i*20+10, 0, 0), grey).echo()

nb = monde.count('\n')

f = open("WORLD", "w")
f.write(str(nb)+'\n'+monde)




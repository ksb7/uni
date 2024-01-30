class Vector():
    def __init__(self, Ax, Bx, Ay, By):
        self._Ax = Ax
        self._Bx = Bx
        self._Ay = Ay
        self._By = By

    def from_string(cls, str_value: str):
        return cls.__init__()

    def __str__(self):
        return f"A[{self.Ax}, {self.Ay}] B[{self.Bx}, {self.By}]"

    def save(self, filename):
        with open(filename, "w") as file:
            file.write(str(self.Ax))
            file.write(str(self.Bx))
            file.write(str(self.Ay))
            file.write(str(self.By))

    def load(self, filename):
        with open(filename, "r") as file:
            args_list = file.read()
            Ax = int(args_list[0])
            Bx = int(args_list[1])
            Ay = int(args_list[2])
            By = int(args_list[3])

    @classmethod
    def from_string(cls, str_value):
        args_list = str_value.split(' ')
        Ax = int(args_list[0])
        Bx = int(args_list[1])
        Ay = int(args_list[2])
        By = int(args_list[3])
        return cls(Ax, Bx, Ay, By)

    @property
    def Ax(self):
        return self._Ax;

    @Ax.setter
    def Ax(self, value):
        self._Ax = value

    @property
    def Bx(self):
        return self._Bx;

    @Bx.setter
    def Bx(self, value):
        self._Bx = value

    @property
    def Ay(self):
        return self._Ay;

    @Ay.setter
    def Ay(self, value):
        self._Ay = value

    @property
    def By(self):
        return self._By;

    @By.setter
    def By(self, value):
        self._By = value

class VectorCollection():
    def __init__(self, data):
        self._date = [data]

    def __str__(self):
        return "Vector Collection class"

    @property
    def date(self):
        return self._date;

    @date.setter
    def date(self, value):
        self._date = value
        
    def add(self, value):
        self._date.append(value)

    def remove(self, index):
        del self._date[index]

    def save(self, filename):
        with open(filename, "w") as file:
            for index, vector in enumerate(self._date):
                file.write(str(index))
                file.write(str(vector.Ax))
                file.write(str(vector.Bx))
                file.write(str(vector.Ay))
                file.write(str(vector.By))
                
    def load(self, filename):
        with open(filename, "r") as file:
            args_list = [int(i) for i in file.read()]
            i = 0
            while i < len(args_list):
                index = int(args_list[i])
                self._date[index].Ax = int(args_list[i+1])
                self._date[index].Bx = int(args_list[i+2])
                self._date[index].Ay = int(args_list[i+3])
                self._date[index].By = int(args_list[i+4])
                i = i+5

    def __getitem__(self, index):
        return f"A[{self.date[index].Ax}, {self.date[index].Ay}], B[{self.date[index].Bx}, {self.date[index].By}]" 
                

    
exempluVector1 = Vector(2, 3, 4, 5)
print("Vector exemplu original: " + exempluVector1.__str__())
exempluVector1.save("file.txt")
exempluVector1.load("file.txt")
print("Vector exemplu dupa save si load: " + exempluVector1.__str__())
exempluVector2 = Vector.from_string("6 7 8 9")
print("Vector exemplu from string: " + exempluVector2.__str__())

exempluColectie = VectorCollection(exempluVector1)
exempluColectie.add(exempluVector2)
print("Vector Collection exemplu indexare: " + exempluColectie[1])
exempluColectie.save("fisier.txt")
exempluColectie.load("fisier.txt")
print("Vector Collection exemplu dupa save si load: " + exempluColectie[1])

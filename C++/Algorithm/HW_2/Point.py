import random
import operator


class Point(object):
    

    def __init__(self, x, y):
        self.x = x
        self.y = y

    @staticmethod
    def cross(o, a, b):#find inner angle from this three points
        return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x)

    @staticmethod
    def findConvexHull(pointsList):
        #sort points by x and y
        pointsList = sorted(pointsList, key=operator.attrgetter('x', 'y'))
        numOfVextexs = 0
        vextexs = []

        #find lower convex hull
        for i in range(len(pointsList)):
            #have nore than two vextexs and check next point's inner angle is getter than 180 
            while (numOfVextexs >= 2 and Point.cross(vextexs[numOfVextexs - 2], vextexs[numOfVextexs - 1], pointsList[i]) <= 0):
                #if not pop the last vertex
                vextexs.pop()
                numOfVextexs -= 1
            vextexs.append(pointsList[i])
            numOfVextexs += 1
        
        #find upper convex hull
        start = numOfVextexs + 1
        for i in range(len(pointsList) - 2, -1, -1):
            while (numOfVextexs >= start and Point.cross(vextexs[numOfVextexs - 2], vextexs[numOfVextexs - 1], pointsList[i]) <= 0):
                vextexs.pop()
                numOfVextexs -= 1
            vextexs.append(pointsList[i])
            numOfVextexs += 1
        
        return vextexs

    
    @staticmethod
    def randomPoints(size):
        pointList = []
        index = 0
        while(size != index):
            x = random.randint(0, 1000)
            y = random.randint(0, 1000)
            p = Point(x, y)
            if (p in pointList):
                continue
            pointList.append(p)
            index += 1
        return pointList


    def __str__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"

    def __repr__(self):
        return str(self)
